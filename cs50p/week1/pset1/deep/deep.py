def main():
    answer = input("Yes? ").strip(" ").lower()
    if answer == str(42) or answer == "forty-two" or answer == "forty two":
        print("Yes")
    else:
        print("No")


main()
