import sys
import random
from pyfiglet import Figlet

argv = sys.argv

size = len(argv)

figlet = Figlet()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

try:
    if size > 2 and (argv[1] == '-f' or '--font') and (argv[2] in list):
        f = Figlet(font = argv[2])
    elif size < 2:
        
except:
    print("Invalid usage")
    sys.exit()

input = input("Input: ")

print (f.renderText(input))