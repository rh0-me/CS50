# TODO
def main():
    # Get a positive number between 0 and 8 as Input
    while True:
        try:
            height = int(input("Height: "))
            if 9 > height > 0:
                break
            else:
                continue
        except:
            continue
    # Print every row of the pyramid
    for i in range(height):
        num = i + 1
        for j in range(height - num):
            print(" ", end="")
        for j in range(num):
            print("#", end="")
        print("  ", end="")
        for j in range(num):
            print("#", end="")
        print()
        # print(" " * (height - i + 1), end='')
        # print("#" * (i+1), end='')
        # print("  ", end='')
        # print("#" * (i+1), end='')
        # print(" " * (height - i + 1), end='')
        # print()


if __name__ == '__main__':
    main()
