from bank import value


def main():
    test_hello()
    test_startswith_h()
    test_no_greeting()
    test_good_morning()


def test_hello():
    assert value("hello") == 0
    assert value("HELLO") == 0


def test_startswith_h():
    assert value("hey") == 20
    assert value("hi") == 20
    assert value("howdy") == 20


def test_no_greeting():
    assert value("") == 100


def test_good_morning():
    assert value("Good Morning!") == 100


if __name__ == "__main__":
    main()
