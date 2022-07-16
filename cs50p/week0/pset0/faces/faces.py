def main():
    x = input("Say something: ")
    print(convert(x));


def convert(x):
    return x.replace(":)","🙂").replace(":(","🙁")

main()