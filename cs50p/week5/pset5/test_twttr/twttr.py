def main():
    text = input("Input: ")
    text = shorten(text)
    print(text)


def shorten(word):
    vowels = "AaEeIiOoUu"
    for char in vowels:
        if char in word:
            word = word.replace(char, "")
    return word


if __name__ == "__main__":
    main()
