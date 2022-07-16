import random
import sys


def main():
    while True:
        user_level = input("Level: ")
        try:
            user_level = int(user_level)
            if user_level > 0:
                break
        except:
            pass
    n = random.randint(1, user_level)
    while True:
        guess = input("Guess: ")
        try:
            guess = int(guess)
            if guess < 1:
                continue
        except:
            continue
        if guess < n:
            print("Too small!")
            continue
        elif guess > n:
            print("Too large!")
            continue
        else:
            print("Just right!")
            sys.exit(0)


if __name__ == "__main__":
    main()
