import sys


def main():
    # Validate argv count
    if len(sys.argv) < 2:
        print("Too few command-line arguments")
        sys.exit(1)
    if len(sys.argv) > 2:
        print("Too many command-line arguments")
        sys.exit(1)
    # Validate python file
    filename = sys.argv[1].rstrip()
    if not filename.endswith(".py"):
        print("Not a Python file")
        sys.exit(1)
    # Validate if file exists
    try:
        file = open(filename)
    except:
        print("File does not exist")
        sys.exit(1)
    loc = get_loc(file)
    file.close()
    print(loc)


def get_loc(file):
    loc = 0
    lines = file.readlines()
    for line in lines:
        if line.isspace():
            continue
        line = line.lstrip()
        if (line[0] == "#"):
            continue
        loc += 1
    return loc


if __name__ == "__main__":
    main()
