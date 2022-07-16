def main():
    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }
    items = []
    order = ""
    while True:
        try:
            order = input("Item: ")
        except EOFError:
            print()
            break
        else:
            if order.title() in menu:
                sum = 0
                items.append(menu[order.title()])
                for i in items:
                    sum += i
                print(f"${sum:.2f}")
    # while True:
    #     try:
    #         order = input("Item: ").casefold()
    #     except EOFError:
    #         print("f")
    #         break
    #     else:
    #         try:
    #             items.append(menu[order.title()])
    #         sum = 0
    #         for i in items:
    #             sum += i
    #         print(f"${sum}")


main()
