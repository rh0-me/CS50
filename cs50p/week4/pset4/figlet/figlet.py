import sys
import random
from pyfiglet import Figlet


def main():

    # Argumentvalidation
    if not(len(sys.argv) == 1 or len(sys.argv) == 3):
        sys.exit("Invalid usage")
    figlet = Figlet()
    fonts = figlet.getFonts()
    f = ""
    if len(sys.argv) == 3:
        if not(sys.argv[1] == "-f" or sys.argv[1] == "--font"):
            sys.exit("Invalid usage")
        if not(sys.argv[2] in fonts):
            sys.exit("Invalid usage")
        f = sys.argv[2]

    user_input = input("Input: ")
    if (f == ""):
        f = random.choice(fonts)
    figlet.setFont(font=f)
    print("Output: ")
    print(figlet.renderText(user_input))


if __name__ == "__main__":
    main()
