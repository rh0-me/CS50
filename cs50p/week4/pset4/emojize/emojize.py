import emoji


def main():
    while True:
        user_input = input("Input: ")
        try:
            user_output = emoji.emojize(user_input,language='alias')
        except:
            continue
        print(user_output)
        break

if __name__ == '__main__':
    main()
