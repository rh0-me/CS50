def main():
    expression = input("Expression: ").strip(" ")
    x, y, z = expression.split(" ")
    if y == "*":
        result = float(x) * float(z)
    elif y == "/":
        result = float(x)/float(z)
    elif y == "+":
        result = float(x)+float(z)
    elif y == "-":
        result = float(x) - float(z)
    else:
        result = "Incorrect Input"
    print(result)


main()
