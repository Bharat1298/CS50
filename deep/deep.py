response = (input("What is the Answer to the Great Question of Life, the Universe, and Everything? ")).strip().lower()

print("Yes") if response == "42" or response == "forty-two" or response == "forty two" else print("No")