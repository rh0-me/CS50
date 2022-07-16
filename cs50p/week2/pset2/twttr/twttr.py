def main():
    text = input("Input: ")
    output = ""
    for s in text:
        if s.casefold() == "a" or s.casefold() == "e" or s.casefold() == "i" or s.casefold() == "o" or s.casefold() == "u":
            continue
        output += s
    print(f"Output: {output}")


main()
