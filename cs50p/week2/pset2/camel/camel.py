def main():
    variable = input("camelCase: ").strip(" ")
    variable = to_snake_case(variable)
    print(f"{variable}")

def to_snake_case(name):
    result = ""
    for n in name:
        if n.isupper():
            result += "_"
            result += n.lower()
        else:
            result += n
    return result


main()
