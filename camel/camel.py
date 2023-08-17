input = input("camelCase: ").strip()
newword = ""

for letter in input:
    if letter.isupper():
        letter = "_" + letter.lower()
    newword += letter


print(newword)