import re
import sys


def main():
    print(validate(input("IPv4 Address: ").strip()))


def validate(ip):
    if re.search(r
    "^[0-9]|[1-90-9]|[1-20-50-5]\.[0-9]|[1-90-9]|[1-20-50-5]\.[0-9]|[1-90-9]|[1-20-50-5]\.[0-9]|[1-90-9]|[1-20-50-5]$", ip):
        return True
    else:
        return False


if __name__ == "__main__":
    main()
