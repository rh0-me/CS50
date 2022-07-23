from numb3rs import validate


def test_legit():
    assert validate("255.255.255.255") == True
    assert validate("127.0.0.1") == True


def test_not_legit():
    assert validate("512.512.512.512") == False
    assert validate("1.2.3.10002") == False
    assert validate("cat") == False
