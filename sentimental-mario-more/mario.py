def main():
    size = 0

    while size < 1 or size > 8:
        size = int(input("How big is the pyramid? "))

    rowsLeft = size

    for rows in range(size):

        for space in range(rowsLeft - 1):
            print(" ", end = "")

        for left in range(rows):
            print("#", end = "")

        print("  ", end = "")

        for right in range(rows):
            print("#", end = "")

        rowsLeft -= 1
        print("")

if __name__ == "__main__":
    main()