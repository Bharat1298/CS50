input = input("Greeting: ").strip()

word = input.lower()

print(word[0])

if word[0] == "hello":
    print("$0")

# elif word.startswith('h'):
#     print("$20")

else:
    print("$100")

