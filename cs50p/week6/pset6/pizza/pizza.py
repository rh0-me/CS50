import sys
from tabulate import tabulate
import csv


def main():
    if len(sys.argv) < 2:
        print("Too few command-line arguments")
        sys.exit(1)

    if len(sys.argv) > 2:
        print("Too many command-line arguments")
        sys.exit(1)

    if not sys.argv[1].endswith(".csv"):
        print("Not a CSV file")
        sys.exit(1)

    filename = sys.argv[1]

    try:
        file = open(filename)
    except:
        print("File does not exist")
        sys.exit(1)
    reader = csv.DictReader(file)
    headers = reader.fieldnames
    items = []
    for line in reader:
        items.append(line)
    print(tabulate(items, headers="keys", tablefmt="grid"))


if __name__ == "__main__":
    main()
