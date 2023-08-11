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
    names = db.execute("SELECT username FROM users WHERE id == ?", session["user_id"])

    name = names[0]["username"]

    stocks = db.execute("SELECT stock FROM purchases WHERE userID == ?", session["user_id"])

    print(stocks)

    return render_template("index.html", name = name, )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Enter Valid Ticker", 403)

        stock = lookup(request.form.get("symbol"))

        if stock == None:
            return apology("Ticker Not Valid", 403)

        shares = int(request.form.get("shares"))

        if shares < 1:
            return apology("Shares Not Valid", 403)

        price = stock['price']

        userRequest = price * shares

        cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])

        balance = int(cash[0]["cash"])

        if balance > userRequest:
            #buy shares
            balance -= userRequest
            db.execute("UPDATE users SET cash = ? WHERE id == ?", balance, session["user_id"])
            db.execute("INSERT INTO purchases(userID, stock, price, shares, orderTotal, time) VALUES(?, ?, ?, ?, ?, CURRENT_TIMESTAMP)", session["user_id"], stock["name"], price, shares, userRequest)
        else:
            return apology("Cannot Afford", 403)

        return render_template("index.html")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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

        try:
            stock = lookup(ticker)
        except:
            return apology("Invalid stock ticker", 403)

        name = stock['name']

        price = stock['price']

        symbol = stock['symbol']

        return render_template("stock.html", name = name, price = price, symbol = symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Invalid username", 403)

        if not request.form.get("password"):
            return apology("Invalid password", 403)

        if not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("password"):
            return apology("Passwords must match", 403)

        username = request.form.get("username")

        hash = generate_password_hash(request.form.get("password"))

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)" , username, hash)
        except ValueError:
            return apology("Username is taken", 403)

        id = db.execute('SELECT * FROM users WHERE username == ?', username)

        session["user_id"] = id[0]["id"]

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
