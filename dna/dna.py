import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Incorrect usage")
        return 1

    # TODO: Read database file into a variable

    dnaData = []
    dnaCheck = []

    with open(sys.argv[1], 'r') as file:
        check = csv.reader(file)
        count = 0

        for str in check:
            if count == 0:
                for char in str:
                    if char != 'name':
                        dnaCheck.append(char)
                break
            break

    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for data in reader:
            dnaData.append(data)

    # TODO: Read DNA sequence file into a variable

    sequenceData = []

    with open(sys.argv[2]) as file:
        database = csv.reader(file)
        for i in database:
            for j in i:
                sequenceData.append(j)

    # TODO: Find longest match of each STR in DNA sequence

    for str in dnaCheck:
        longest_match(sequenceData, str)

    print(dnaData)
    print(dnaCheck)
    print(sequenceData)

    # for sequence in dnaData:
    #     if sequence in sequenceData:
    #         longest_match(sequenceData, sequence)


    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
