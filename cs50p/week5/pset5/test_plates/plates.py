def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    # length of plate
    if len(s) > 6 or len(s) < 2:
        return False
    # first two chars are letters
    if not(s[0].isalpha() and s[1].isalpha()):
        return False
    # no periods spaces or punctuation marks -> alphanumeric
    for i in s:
        if not i.isalnum():
            return False
    # search for number check for continuity till the end of the string
    # get index
    is_number = False
    for i in range(len(s)):
        # Check for first occurence of a number and if it's a zero
        if s[i].isnumeric() and not is_number:
            if s[i] == "0":
                return False
            else:
                is_number = True
        # After first occurence of a number, check if characters thereafter are not numeric
        if is_number:
            if not s[i].isnumeric():
                return False
    return True


if __name__ == "__main__":
    main()
