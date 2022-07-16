import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("python dna.py database sequence")
        sys.exit(0)
    sequence = ""
    keys = []
    suspects = []
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r")as file:
        reader = csv.DictReader(file)
        keys += reader.fieldnames
        for row in reader:
            suspects += [row]
        # for row in reader:
        #     suspect = {}
        #     for i in range(len(keys)):
        #         if i < 1:
        #             suspect[keys[i]] = row[keys[i]]
        #         else:
        #             suspect[keys[i]] = int(row[keys[i]])
        #     suspects += [suspect]
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r")as file:
        sequence = file.readline()
    # TODO: Find longest match of each STR in DNA sequence
    profile = {"name": "culprit"}
    for i in range(1, len(keys)):
        profile[keys[i]] = str(longest_match(sequence, keys[i]))
    # TODO: Check database for matching profiles
    get_match(suspects, profile, keys)
    return


def get_match(suspects, profile, keys):

    for i in range(1, len(keys)):
        innocent = []
        for j in suspects:
            if profile[keys[i]] != j[keys[i]]:
                innocent += [j]
        for j in innocent:
            suspects.remove(j)
    if len(suspects) == 0:
        print("No match.")
    else:
        print(suspects[0][keys[0]])


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
