import numpy as np

def f(x: float, a: float = 1) -> float:
    """Calculate f(x) = ln(x) - cos(x)"""
    return np.log(x) - a * np.cos(x)


def df(x: float, a: float = 1) -> float:
    """Calculate first derivative f(x) = 1/x + sin(x)"""
    return 1 / x + a * np.sin(x)


def ddf(x: float, a: float = 1) -> float:
    """Calculate second derivative f(x) = 1/x^2 + cos(x)"""
    return -1 / x**2 + a * np.cos(x)


def chr(x: float, b: float, c: float = 1) -> float:
    """Calculate chord method for right boundary"""
    return x - (f(x, c) / (f(b, c) - f(x, c))) * (b - x)


def nw(x: float, c: float = 1) -> float:
    """Calculate Newton method"""
    return x - f(x, c) / df(x, c)


def calc_comb(a: float, b: float, c: float = 1, eps: float = 1e-5):
    """Calculate root by chord method"""
    i = 0
    history = []
    while abs(b - a) > eps:
        i += 1
        a_p, b_p = a, b
        a, b = nw(a_p, c), chr(a, b_p, c)
        history.append({ 'a': a, 'b': b, 'a_p': a_p, 'b_p': b_p })
    return (a + b) / 2, i, history


def calc_nw(x: float, c: float = 1, eps: float = 1e-5):
    """Calculate root by Newton method"""
    i: int = 0
    while abs(nw(x, c) - x) > eps:
        i += 1
        x = nw(nw(x, c), c)
    return nw(x, c), i
