def main():
    months_w = [
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    ]
    year = 0
    month = 0
    day = 0
    while True:
        date = input("Date: ").strip()
        if "/" in date:
            try:
                month, day, year = date.split("/")
            except ValueError:
                print("ValueError: /")
                continue
            else:
                try:
                    month = int(month)
                except ValueError:
                    continue
                else:
                    if month > 12:
                        continue
        elif "," in date:
            tmp, year = date.split(",",)
            try:
                month, day = tmp.split()
            except ValueError:
                print("ValueError: ,")
            if not month in months_w:
                continue
            for i in range(len(months_w)):
                if months_w[i] == month:
                    month = i + 1
                    break
        else:
            continue
        try:
            year = int(year)
            month = int(month)
            day = int(day)
        except ValueError:
            print("ValueError: Converting to Int")
        else:
            if day > 31:
                continue
            print(f"{year:04}-{month:02}-{day:02}")
            return 0


main()
