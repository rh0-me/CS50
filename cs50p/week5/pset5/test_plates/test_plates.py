from plates import is_valid


def test_default():
    assert is_valid("AAA222") == True


def test_start():
    assert is_valid("AA222") == True
    assert is_valid("X222") == False
    assert is_valid("55") == False
    assert is_valid("AB") == True
    assert is_valid("A2") == False

def test_length():
    assert is_valid("SDFS56") == True
    assert is_valid("AAA22277") == False
    assert is_valid("A") == False



def test_numbers():
    assert is_valid("AAA424") == True
    assert is_valid("AAA022") == False
    assert is_valid("AA34A2") == False
    assert is_valid("74FV65") == False
    assert is_valid("7489") == False



def test_not_alphanum():
    assert is_valid("AAA,2") == False
    assert is_valid("AA.22") == False
    assert is_valid("AA 22") == False
    assert is_valid("AA!22") == False
    assert is_valid("") == False
    assert is_valid("{[§$%])") == False
    assert is_valid("5S !") == False




