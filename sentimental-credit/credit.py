from cs50 import get_int
import math

def main():
    card = get_int("Card Number: ")

    sum = checksum(card)

    count = 0

    digitCount = card

    while digitCount > 0:
         digitCount /= 10
         count += 1


    if sum % 10 == 0:
         if count == 13:
              print("VISA")
         elif count == 15 and ((card / 10000000000000 == 34) or (card / 10000000000000 == 37)):
              print("AMEX")
         elif count == 16:
              if card / 1000000000000000 < 5:
                   print("VISA")
              elif (card / 100000000000000 < 56) and (card / 100000000000000 > 50):
                   print("MASTERCARD")
              else:
                   print("INVALID")
         else:
              print("INVALID")
    else:
         print("INVALID")


def checksum(card):

     card1 = 0
     card2 = 0
     holder = 10
     holder2 = 1
     num1 = math.trunc(card / 10)
     num2 = card
     sum1 = 0
     sum2 = 0

     while num1 > 0:
          remainder = num1 % 10
          num1 /= 100

          card1 += remainder * holder

          holder *= 100

     while num2 > 0:
          remainder2 = num2 % 10
          num2 /= 100

          sum2 += remainder2

          card2 += remainder2 * holder2

          holder2 *= 100

     remainders = []

     i = 0

     while num1 > 0:
          remainders.append((num1 % 10) * 2)
          num1 /= 10

          if remainder[i] >= 10:

               x = remainders[i]

               sum1 += x % 10

               x /= 10

               sum1 += x % 10
          else:
               sum1 += remainder[i]

          i += 1

     return sum1 + sum2


if __name__ == "__main__":
     main()