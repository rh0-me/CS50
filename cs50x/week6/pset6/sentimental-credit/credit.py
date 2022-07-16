# TODO
import sys


def main():
    try:
        credit_card = int(input("Number: "))
    except:
        print("Credit card not valid")
        sys.exit(1)
    # Check for Luhns Algorithmn
    if (not checksum(credit_card)):
        print("INVALID")
        sys.exit(0)
    # Check if AMEX
    if is_AMEX(credit_card):
        print("AMEX")
    # Check if Mastercard
    elif is_MC(credit_card):
        print("MASTERCARD")
    # Check if Visa
    elif is_VISA(credit_card):
        print("VISA")
    # Card is invalid
    else:
        print("INVALID")
    sys.exit(0)

# Length and Beginning of given credit card requirements


def is_AMEX(number):
    result = False
    number = str(number)
    length = len(number)
    if length == 15 and number[0] == "3" and (number[1] == "4" or number[1] == "7"):
        result = True
    return result

# Length and Beginning of given credit card requirements


def is_MC(number):
    result = False
    number = str(number)
    length = len(number)
    if length == 16 and (number[0:2] == "51" or number[0:2] == "52" or number[0:2] == "53" or number[0:2] == "54" or number[0:2] == "55"):
        result = True
    return result

# Length and Beginning of given credit card requirements


def is_VISA(number):
    result = False
    number = str(number)
    length = len(number)
    if (length == 16 or length == 13) and number[0] == "4":
        result = True
    return result


def checksum(number):
    """Luhn's Algorithmn """
    result = False
    if number < 0:
        return result
    length = len(str(number))
    sum2 = 0
    sum = 0

    for i in range(length):
        if i % 2 == 1:
            num = (number % 10)*2
            if num > 9:
                sum2 += num % 10
                num //= 10
            sum2 += num
        else:
            sum += number % 10
        number //= 10
    if (sum + sum2) % 10 == 0:
        result = True
    return result


if __name__ == '__main__':
    main()
