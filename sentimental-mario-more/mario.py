def main():
    size = 0

    while size < 1 or size > 8:
        size = int(input("How big is the pyramid? "))

    rowsLeft = size

    for rows in range(size):

        for space in range(rowsLeft - 1):
            print(" ")

        for left in range(rows):
            print("#", end: "")

        print("  ")

        for right in range(rows):
            print("#")

        rowsLeft -= 1
        print("")

if __name__ == "__main__":
    main()