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

     print(brand)

def checksum(strCard):
     card = int(strCard)
     valid = False
     holder = 10
     holder2 = 1
     sum1 = 0
     sum2 = 0
     sum = 0
     num1 = 0
     num2 = 0

if __name__ == '__main__':
     main()