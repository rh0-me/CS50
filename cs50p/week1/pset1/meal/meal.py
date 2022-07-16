def main():
    daytime = input("What time is it? ").strip(" ")
    timeInFloat = convert(daytime)
    if 7 <= timeInFloat <= 8:
        print("breakfast time")
    elif 12 <= timeInFloat <= 13:
        print("lunch time")
    elif 18 <= timeInFloat <= 19:
        print("dinner time")


def convert(time):
    if "a.m" in time:
        time.strip("amp.")
        x, y = time.split(":")
        number = float(x) + (float(y)/60)
    elif "p.m" in time:
        time.strip("amp.")
        x, y = time.split(":")
        number = 2*float(x) + (float(y)/60)
    else:
        x, y = time.split(":")
        number = float(x) + (float(y)/60)
    return number


if __name__ == "__main__":
    main()
