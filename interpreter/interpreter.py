user = input("Expression: ").split(" ")
num1 = int(user[0])
num2 = int(user[2])
operator = user[1]

match operator:
    case "+":
        print("%.1f" % (num1 + num2))
    case "-":
        print("%.1f" % (num1 - num2))
    case "*":
        print("%.1f" % (num1 * num2))
    case "/":
        print("%.1f" % (num1 / num2))
    case _:
        print("Invalid Input")