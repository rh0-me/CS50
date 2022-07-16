def main():
    names = []
    while True:
        try:
            names += [input("Name: ")]
        except EOFError:
            break
    print()
    display_names(names)
    print()


def display_names(names):
    print("Adieu, adieu, to ", end="")
    if len(names) == 1:
        print(names[0])
    elif len(names) == 2:
        print(f"{names[0]} and {names[1]}")
    else:
        for i in range(len(names)):
            if i == len(names) - 1:
                print(f"and {names[i]}", end="")
            else:
                print(f"{names[i]}, ", end="")


if __name__ == "__main__":
    main()
