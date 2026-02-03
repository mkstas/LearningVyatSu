# [0,8;1,7]

import math

def f(x: float, a: float = 1) -> float:
    return math.log(x) - a * math.cos(x)

def df(x: float, a: float = 1) -> float:
    return 1 / x + a * math.sin(x)

def newton(x: float) -> float:
    return x - f(x) / df(x)

def calc_root(x: float, eps: float = 1e-5) -> float:
    while True:
        if abs(newton(x) - x) < eps:
            return newton(x)
        x = newton(newton(x))

print(f"{calc_root(0.8):.6f}")
