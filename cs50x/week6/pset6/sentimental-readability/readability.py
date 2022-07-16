# TODO
def main():
    text = input("Text: ")
    # Calculate words, letters and sentences
    num_letters = 0
    num_words = text.count(" ") + 1
    num_sentences = 0
    for i in text:
        if i == "." or i == "?" or i == "!":
            num_sentences += 1
        if i.isalpha():
            num_letters += 1
    # Calculate variables for CLI
    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100
    cli = round(0.0588 * L - 0.296 * S - 15.8)
    # Output based on cli
    if cli >= 16:
        print("Grade 16+")
    elif cli < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {cli}")


if __name__ == "__main__":
    main()
