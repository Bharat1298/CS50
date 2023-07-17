from pyfiglet import Figlet
from sys import argv
import random

figlet = Figlet()

input = input("Input: ").strip()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

if len(argv) > 2 and argv[1] == '-f' or '--font':
    input = argv[2]

print (f.renderText(input))