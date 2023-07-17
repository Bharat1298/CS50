from pyfiglet import Figlet
import random

figlet = Figlet()

input = input("Input: ").strip()

list = figlet.getFonts()

num = random.randint(0, len(list))

f = Figlet(font = list[num])

print (f.renderText(input))