from pyfiglet import Figlet
import sys
import random

argv = sys.argv

figlet = Figlet()

input = input("Input: ").strip()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

if len(argv) > 2 and argv[1] == '-f' or '--font':
    if argv[2] in list:
        f = Figlet(font = argv[2])
    else:
        print("Invalid usage")
        sys.exit
elif len(argv) > 2:
    print("Invalid usage")
    sys.exit

print (f.renderText(input))