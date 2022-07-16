def main():
    price = 50
    amount_due = price
    paid = 0
    change = 0
    while True:
        print(f"Amount Due: {amount_due}")
        inserted = int(input("Insert Coin: "))
        if inserted == 25 or inserted == 10 or inserted == 5:
            paid += inserted
        amount_due = price - paid
        if amount_due <= 0:
            change = paid - price
            amount_due = 0
            print(f"Change Owed: {change}")
            break
main()
