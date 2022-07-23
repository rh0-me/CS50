def main():
    while True:
        user_input = input("Fraction: ").strip()
        try:
            percentage = convert(user_input)
        except(ValueError, ZeroDivisionError):
            continue
        break
    output = gauge(percentage)
    print(output)


def convert(to_convert):

    x, y = to_convert.split("/")
    x = int(x)
    y = int(y)
    if y == 0:
        raise ZeroDivisionError
    if x > y:
        raise ValueError
    return round(x/y*100)


def gauge(perc):
    if perc <= 1:
        return "E"
    elif perc >= 99:
        return "F"
    else:
        return f"{perc}%"


if __name__ == "__main__":
    main()
