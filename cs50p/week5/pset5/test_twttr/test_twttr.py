from twttr import shorten


def main():
    test_lower()
    test_upper()
    test_numbers()
    test_special()


def test_lower():
    assert shorten("abcdefghijklmnopqrstuvwxyz") == "bcdfghjklmnpqrstvwxyz"
    assert shorten("abbaasusuibibobboboo") == "bbssbbbbb"


def test_upper():
    assert shorten("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == "BCDFGHJKLMNPQRSTVWXYZ"
    assert shorten("ABBAASUSUIBIBOBBOBOO") == "BBSSBBBBB"


def test_numbers():
    assert shorten("abadfu14244209dfsijaa8u8") == "bdf14244209dfsj88"


def test_special():
    assert shorten("afas.a-!.,:,;fauioamehaofna") == "fs.-!.,:,;fmhfn"

if __name__ == "__main__":
    main()
