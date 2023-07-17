from pyfiglet import Figlet
from sys import argv
import random

figlet = Figlet()

input = input("Input: ").strip()

list = figlet.getFonts()

num = random.randint(0, len(list))

if argv > 1 and argv[1] == '-f' or '--font':
    input = argv[2]

f = Figlet(font = list[num])

print (f.renderText(input))