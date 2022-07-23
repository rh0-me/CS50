from PIL import Image
from PIL import ImageOps
import sys


def main():
    # Arg's length validation
    if len(sys.argv) < 3:
        print("Too few command-line arguments")
        sys.exit(1)
    if len(sys.argv) > 3:
        print("Too many command-line arguments")
        sys.exit(1)

    # Fileextension validation
    if not (sys.argv[1].lower().endswith(".png") or sys.argv[1].lower().endswith(".jpg") or sys.argv[1].lower().endswith(".jpeg")):
        print("Invalid input")
        sys.exit(1)
    if not (sys.argv[2].lower().endswith(".png") or sys.argv[2].lower().endswith(".jpg") or sys.argv[2].lower().endswith(".jpeg")):
        print("Invalid output")
        sys.exit(1)
    if sys.argv[1][sys.argv[1].rfind("."):].lower() != sys.argv[2][sys.argv[2].rfind("."):].lower():
        print("Input and output have different extensions")
        sys.exit(1)

    # File validation
    try:
        with Image.open(sys.argv[1]) as input_image, Image.open("shirt.png") as shirt_image:
            ImageOps.fit(input_image, shirt_image.size)
            input_image.paste((shirt_image))
            input_image.save(sys.argv[2])
    except IOError:
        print("Input does not exist")
        sys.exit(1)


if __name__ == "__main__":
    main()
