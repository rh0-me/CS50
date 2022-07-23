import sys
import csv


def main():
    if len(sys.argv) < 3:
        print("Too few command-line arguments")
        sys.exit(1)
    if len(sys.argv) > 3:
        print("Too many command-line arguments")
        sys.exit(1)
    if not sys.argv[1].endswith(".csv"):
        print("Could not read invalid_file.csv")
        sys.exit(1)
    try:
        # Read old csv
        with open(sys.argv[1]) as file:
            reader = csv.DictReader(file)
            students = []
            for row in reader:
                students.append(row)

    except IOError:
        print("Could not read invalid_file.csv")
        sys.exit(1)
    # Clean data
    students2 = []
    for student in students:
        last, first = student["name"].split(",")
        last = last.strip()
        first = first.strip()
        house = student["house"].strip()
        students2.append(
            {"first": first, "last": last, "house": house})
    # Write to new csv
    with open(sys.argv[2], "w") as file:
        fieldnames = ["first", "last", "house"]
        writer = csv.DictWriter(file, fieldnames)
        writer.writeheader()
        writer.writerows(students2)


if __name__ == "__main__":
    main()
