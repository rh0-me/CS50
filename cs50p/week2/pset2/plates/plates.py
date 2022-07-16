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
    if not(s[0].isalpha() or s[1].isalpha()):
        return False
    # no periods spaces or punctuation marks -> alphanumeric
    for i in s:
        if not i.isalnum():
            return False
    # search for number check for continuity till the end of the string
    # get index
    is_number = False
    for i in range(len(s)):
        if s[i].isnumeric() and not is_number:
            if s[i] == "0":
                return False
            else:
                is_number = True
        if is_number:
            if not s[i].isnumeric():
                return False
    return True


main()
