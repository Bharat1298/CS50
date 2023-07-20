from cs50 import get_string

def main():
    text = get_string("Text: ")

    letter = letters(text)

    word = words(text)

    sentence = sentences(text)

    L = letter / word * 100

    S = sentence / word * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def letters(text):
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count

def words(text):
    count = 1
    for char in text:
        if char == ' ':
            count += 1
    return count

def sentences(text):
    count = 0
    for word in text:
        if word == '.' or word == '!' or word == '?':
            count += 1
    return count

if __name__ == "__main__":
    main()