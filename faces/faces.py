def main():
    print(convert(input()))

def convert(string):
    string = string.replace(":(", "🙁")
    string = string.replace(":)", "🙂")
    return string

main()