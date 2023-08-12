import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.filters["look"] = lookup

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = db.execute("SELECT * FROM users WHERE id == ?", session["user_id"])

    name = user[0]["username"]

    purchases = db.execute("SELECT * FROM purchases WHERE userID == ? GROUP BY stock ORDER BY orderTotal DESC", session["user_id"])

    amount = db.execute("SELECT stock, shares FROM (SELECT stock, SUM(shares) AS shares FROM purchases WHERE userID == ? GROUP BY stock) WHERE shares > 0", session["user_id"])

    for stock in amount:
        if int(stock["shares"]) < 0:
            amount.remove(stock)

    cash = user[0]["cash"]

    return render_template("index.html", name = name, purchases = purchases, amount = amount, cash = cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        print(stock)

        if stock == None:
            return apology("Enter Valid Ticker", 400)

        if not request.form.get("symbol"):
            return apology("Enter Valid Ticker", 400)

        if request.form.get("shares") == None:
            return apology("Enter Valid Shares", 400)

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Enter Valid Shares", 400)

        if shares < 1:
            return apology("Shares Not Valid", 400)

        price = stock['price']

        userRequest = price * shares

        cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])

        balance = int(cash[0]["cash"])

        if balance > userRequest:
            balance -= userRequest
            db.execute("UPDATE users SET cash = ? WHERE id == ?", balance, session["user_id"])
            db.execute("INSERT INTO purchases(userID, stock, price, shares, orderTotal, time) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP)", session["user_id"], stock["name"], price, shares, userRequest)
            flash(f'Successfully bought {shares} shares of {stock["name"]} for {usd(userRequest)}')
        else:
            return apology("Cannot Afford", 400)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT * FROM purchases WHERE userID = ?", session["user_id"])
    print(history)
    return render_template("history.html", history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        ticker = request.form.get("symbol")

        if not ticker.isalpha():
            return apology("Invalid stock ticker", 400)

        stock = lookup(ticker)

        if stock == None:
            return apology("Invalid ticker", 400)

        name = stock["name"]

        price = stock["price"]

        symbol = stock["symbol"]

        return render_template("quoted.html", name = name, price = price, symbol = symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Invalid username", 400)

        if not request.form.get("password"):
            return apology("Invalid password", 400)

        if not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("password"):
            return apology("Passwords must match", 400)

        username = request.form.get("username")

        hash = generate_password_hash(request.form.get("password"))

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)" , username, hash)
        except ValueError:
            return apology("Username is taken", 400)

        id = db.execute('SELECT * FROM users WHERE username == ?', username)

        session["user_id"] = id[0]["id"]

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    portfolio = db.execute("SELECT stock, shares FROM (SELECT stock, SUM(shares) AS shares FROM purchases WHERE userID == ? GROUP BY stock) WHERE shares > 0", session["user_id"])
    listOfStocks = []
    for purchase in portfolio:
        listOfStocks.append(purchase["stock"])

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Select a stock", 400)
        else:
            symbol = request.form.get("symbol")

        count = 0

        sell = int(request.form.get("shares"))

        for stock in portfolio:
            if(symbol in stock["stock"]):
                count = stock["shares"]

        if sell > count:
            return apology("Not enough shares", 400)

        state = lookup(symbol)

        print(state)

        price = state["price"]

        print(price)

        db.execute("UPDATE users SET cash = cash + ? WHERE id == ?", price * sell, session["user_id"])
        db.execute("INSERT INTO purchases(userID, stock, price, shares, orderTotal, time) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP)", session["user_id"], state["name"], price, sell * -1, price * sell)

        return redirect("/")
    else:
        return render_template("sell.html", listOfStocks = listOfStocks)

@app.route("/reset", methods=["GET", "POST"])
def reset():
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        usernames = []

        for row in rows:
            usernames.append(row["username"])

        if request.form.get("username") not in usernames:
            return apology("Username not found", 400)

        # Ensure password was submitted
        elif not request.form.get("oldPassword"):
            return apology("must provide old password", 400)

        # Ensure new password was submitted
        elif not request.form.get("newPassword"):
            return apology("must provide new password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmPassword") or request.form.get("confirmPassword") != request.form.get("newPassword"):
            return apology("New Passwords must match", 400)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("oldPassword")):
            return apology("Incorrect Password", 400)

        newPassword = generate_password_hash(request.form.get("newPassword"))

        db.execute("UPDATE users SET hash = ? WHERE username == ?", newPassword, request.form.get("username"))

        return redirect("/")
    else:
        return render_template("reset.html")
