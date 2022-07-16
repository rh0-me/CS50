def main():
    items = {}
    while True:
        try:
            item = input().upper()
        except EOFError:
            break
        else:
            if item in items:
                items[item] += 1
            else:
                items[item] = 1
    sorted_items = sorted(items)
    for i in sorted_items:
        print(f"{items[i]} {i}")



main()
