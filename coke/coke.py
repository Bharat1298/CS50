balance = 50
print(f"Amount Due: {balance}")
while balance > 0:
    remainder = int(input("Insert Coin: "))
    if (remainder == 5 or remainder == 10 or remainder == 25) and balance > 0:
        balance -= remainder
    elif remainder >= balance:
        balance -= remainder
        break
    if balance > 0:
        print(f"Amount Due: {balance}")

print(f"Change Owed: {abs(balance)}")