def main():
    while True:
        try:
            user_input = input("Fraction: ").strip()
            # parse x and y
            x, y = user_input.split("/")
            x = int(x)
            y = int(y)
            if x > y or y == 0:
                raise ValueError
        except ValueError:
            print("ValueError")
        else:
            output(x, y)
            break


def output(x, y):
    if x/y <= 1/100:
        print("E")
    elif x/y >= 99/100:
        print("F")
    else:
        percentage = round(x/y*100)
        print(f"{percentage}%")


main()
