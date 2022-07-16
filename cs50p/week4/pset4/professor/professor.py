import random

levels = [1, 2, 3]


def main():
    n = get_level()
    problems = []
    problems_size = 10
    score = problems_size
    tries_size = 3
    x = "x"
    y = "y"
    for i in range(problems_size):
        problems.append({"x": generate_integer(
            n), "y": generate_integer(n), "wrong_answered": False})

    # Display problems
    for i in problems:
        answer = i["x"] + i["y"]
        for j in range(tries_size):
            user_answer = input(f"{i[x]} + {i[y]} = ")
            if user_answer.isdigit() and int(user_answer) == answer:
                break
            else:
                i["wrong_answered"] = True
                print("EEE")
                if j == tries_size - 1:
                    print(f"{i[x]} + {i[y]} = {answer}")
    # Calculate score
    for i in problems:
        if i["wrong_answered"]:
            score -= 1
    print(f"Score: {score}")


def get_level():

    while True:
        level = input("Level: ")
        try:
            level = int(level)
            if level in levels:
                return level
            else:
                continue
        except:
            continue


def generate_integer(level):
    if level not in levels:
        raise ValueError
    upper_Bound = 0
    if level == 1:
        lower_Bound = 0
    else:
        lower_Bound = pow(10, level - 1)
    for i in range(level):
        upper_Bound += 9*pow(10, i)
    return random.randint(lower_Bound, upper_Bound)


if __name__ == "__main__":
    main()
