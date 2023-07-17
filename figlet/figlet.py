from pyfiglet import Figlet
import sys
import random

argv = sys.argv

figlet = Figlet()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

try:
    if len(argv) > 2 and argv[1] == '-f' or '--font':
        if argv[2] in list:
            f = Figlet(font = argv[2])
except:
    print("Invalid usage")
    sys.exit()

input = input("Input: ").strip()

print (f.renderText(input))