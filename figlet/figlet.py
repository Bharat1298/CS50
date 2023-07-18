import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

argv = ["-f", "--font"]

if len(sys.argv) > 2 and (sys.argv[1] in argv) and (sys.argv[2] in figlet.getFonts()):
    f = Figlet(font = sys.argv[2])

    input = input("Input: ")

    print (f.renderText(input))
elif len(sys.argv) < 2:
    f = Figlet(font = random.choice(figlet.getFonts()))

    input = input("Input: ")

    print (f.renderText(input))
else:
    sys.exit("Invalid usage")
