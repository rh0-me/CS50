from fuel import convert
from fuel import gauge
import pytest


def test_convert():
    assert convert("7/8") == round(7/8*100)


def test_error():
    with pytest.raises(ValueError):
        convert("9/8")
    with pytest.raises(ValueError):
        convert("9cat/dog")
    with pytest.raises(ValueError):
        convert("catdog")
    with pytest.raises(ValueError):
        convert("cat/dog")
    with pytest.raises(ZeroDivisionError):
        convert("9/0")


def test_gauge():
    assert gauge(100) == "F"
    assert gauge(99) == "F"
    assert gauge(0) == "E"
    assert gauge(1) == "E"
    assert gauge(50) == "50%"
