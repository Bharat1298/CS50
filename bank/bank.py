input = input("Greeting: ").strip()

word = input.lower()

if 'hello' in word:
    print("$0")

elif word.startswith('h'):
     print("$20")

else:
    print("$100")

