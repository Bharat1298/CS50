from cs50 import get_string

def main():

     strCard = get_string("Card Number: ").strip()

     one = strCard[0]

     two = strCard[0] + strCard[1]

     sOne = int(one)

     sTwo = int(two)

     valid = checksum(strCard)

     digits = len(strCard)

     brand = ""

     if(valid):
          if digits == 13:
               brand = "VISA"
          elif digits == 15 and (two == "34" or two =="37"):
               brand = "AMEX"
          elif digits == 16:
               if sOne < 5:
                    brand = "VISA"
               elif (sTwo < 56) and (sTwo > 50):
                    brand = "MASTERCARD"
               else:
                    brand = "INVALID"
          else:
               brand = "INVALID"
     else:
          brand = "INVALID"

     print(brand)

def checksum(strCard):
     card = int(strCard)
     holder = 10
     holder2 = 1
     sum1 = 0
     sum2 = 0
     num1 = 0
     num2 = 0
     card1 = card // 10
     card2 = card

     while card1 > 0:
          remainder = card1 % 10
          card1 //= 100

          num1 += remainder * holder

          holder *= 100
     while card2 > 0:
          remainder2 = card2 % 10
          card2 //= 100

          sum2 += remainder2

          num2 += remainder2 * holder2

          holder2 *= 100

     remainders = []

     i = 0

     while num1 > 0:
          remainders.append((num1 % 10) * 2)
          num1 //= 10

          if remainders[i] >= 10 :
               x = remainders[i]

               sum1 += x % 10

               x //= 10

               sum1 += x % 10
          else:
               sum1 += remainders[i]

          i += 1

     if (sum1 + sum2) % 10 == 0:
          valid = True
     else:
          valid = False

     return valid

if __name__ == '__main__':
     main()