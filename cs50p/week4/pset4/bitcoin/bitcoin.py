import requests
import sys
import json

def main():
    if len(sys.argv) != 2:
        print("Missing command-line argument")
        sys.exit(1)
    try:
        n = float(sys.argv[1])
    except:
        print("Command-line argument is not a number")
        sys.exit(1)

    try:
        response = requests.get("https://api.coindesk.com/v1/bpi/currentprice.json")
    except requests.RequestException as e:
        print(e)
        sys.exit(1)

    rate = float(response.json()["bpi"]["USD"]["rate"].replace(",",""))
    price = n * rate
    print(f"${price:,.4f}")



if __name__ == "__main__":
    main()
