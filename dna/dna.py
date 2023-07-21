import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Incorrect usage")
        return 1

    dna = []

    with open(sys.argv[1], 'r') as file:
        dnaReader = csv.DictReader(file)
        for data in dnaReader:
            dna.append(data)

    sequence = []

    with open(sys.argv[2]) as file:
        sequence = file.read()

    check = list(dna[0].keys())[1:]

    match = []

    for str in check:
        match.append(longest_match(sequence, str))

    suspect = ""

    true = False

    #print(match)

    allValues = []

    for person in dna:
        value = []
        counter = 0
        for seq in check:
            value.append(int(person[f'{seq}']))
            counter += 1
        allValues.append(value)

    if match in allValues:
        suspect = "hello"

    print(suspect)

    return suspect


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
