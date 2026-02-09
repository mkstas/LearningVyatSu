import numpy as np
import matplotlib.pyplot as plt

from methods import f, df

def draw_graph() -> None:
    """Draw a graph for function"""
    x_vals = np.linspace(0.8, 1.7)
    y_vals = f(x_vals)

    plt.figure(figsize=(7, 5))
    plt.axhline(0, color='black', linewidth=1, linestyle='-')
    plt.axvline(0, color='black', linewidth=1, linestyle='-')
    plt.plot(x_vals, y_vals, label=r'$f(x) = \ln x - \cos x$', color='blue')
    plt.xlim(0.5, 2.0)
    plt.ylim(-1.0, 1.0)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.2)
    plt.show()

def draw_graph_comb(history):
    """Draw a graph for combine method"""
    x_vals = np.linspace(0.8, 1.7)
    y_vals = f(x_vals)

    plt.figure(figsize=(7, 5))
    plt.axhline(0, color='black', linewidth=1, linestyle='-')
    plt.axvline(0, color='black', linewidth=1, linestyle='-')
    plt.plot(x_vals, y_vals, label=r'$f(x) = \ln x - \cos x$', color='blue')

    for idx, step in enumerate(history[:2]):
        x0 = step['a_p']
        y0 = f(x0)
        x_tan = np.linspace(max(0.5, x0 - 0.5), min(2.0, x0 + 0.5), 50)
        y_tan = y0 + df(x0) * (x_tan - x0)
        plt.plot(x_tan, y_tan, '--', color='darkgreen', linewidth=0.8, label='Касательная' if idx == 0 else None)
        plt.plot(x0, y0, 'o', color='darkgreen', markersize=3)
        plt.plot(step['a'], 0, 'x', color='darkgreen', markersize=3, markeredgewidth=1.5)

        x1, y1 = step['a'], f(step['a'])
        x2, y2 = step['b_p'], f(step['b_p'])

        if abs(x2 - x1) > 1e-12:
            m = (y2 - y1) / (x2 - x1)
            x_chord = np.linspace(max(0.5, min(x1, x2) - 0.3), min(2.0, max(x1, x2) + 0.3), 50)
            y_chord = y1 + m * (x_chord - x1)
            plt.plot(x_chord, y_chord, '-.', color='crimson', linewidth=0.8, label='Хорда' if idx == 0 else None)
            plt.plot(x1, y1, 'o', color='crimson', markersize=3)
            plt.plot(x2, y2, 'o', color='crimson', markersize=3)
            plt.plot(step['b'], 0, 'x', color='crimson', markersize=3, markeredgewidth=1.5)

    plt.xlim(0.5, 2.0)
    plt.ylim(-1.0, 1.0)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.2)
    plt.show()
