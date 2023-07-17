from pyfiglet import Figlet
import sys
import random

argv = sys.argv

size = len(argv)

if size == 2:
    print("Invalid usage")
    sys.exit()

figlet = Figlet()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

if size != 1:
    try:
        if argv[1] == '-f' or '--font' and argv[2] in list:
            f = Figlet(font = argv[2])
    except:
        print("Invalid usage")
        sys.exit()

input = input("Input: ")

print (f.renderText(input))