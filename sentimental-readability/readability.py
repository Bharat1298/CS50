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
    for letter in text:
        if letter.isalpha():
            count += 1

def words(text):

def sentences(text):

if __name__ == "__main__":
    main()