import numpy as np
import matplotlib.pyplot as plt

def f(x: float, a: float = 1) -> float:
    return np.log(x) - a * np.cos(x)


def df(x: float, a: float = 1) -> float:
    return 1 / x + a * np.sin(x)


def ch_a(x: float, a: float) -> float:
    return x - (f(x) / (f(x) - f(a))) * (x - a)


def ch_b(x: float, b: float) -> float:
    return x - (f(x) / (f(b) - f(x))) * (b - x)


def nw(x: float) -> float:
    return x - f(x) / df(x)


def draw_graph() -> None:
    x_vals = np.linspace(0.8, 1.7)
    y_vals = f(x_vals)

    plt.figure(8, 6)
    plt.axhline(0, color='black', linewidth=1, linestyle='-')
    plt.axvline(0, color='black', linewidth=1, linestyle='-')
    plt.plot(x_vals, y_vals, label=r'$f(x) = \ln x - \cos x$', color='blue')
    plt.xlim(0, 4)
    plt.ylim(-1.5, 1.5)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.show()


def draw_graph_comb(history):
    x_vals = np.linspace(0.8, 1.7)
    y_vals = f(x_vals)

    plt.figure(8, 6)
    plt.axhline(0, color='black', linewidth=1, linestyle='-')
    plt.axvline(0, color='black', linewidth=1, linestyle='-')
    plt.plot(x_vals, y_vals, label=r'$f(x) = \ln x - \cos x$', color='blue')

    # Цвета для разных итераций (градиент)
    colors = plt.cm.viridis(np.linspace(0.3, 0.9, len(history)))
    
    # Визуализация каждой итерации
    for idx, step in enumerate(history):
        color = colors[idx]
        xl_old = step['xl_old']
        xr_old = step['xr_old']
        xl_new = step['xl_new']
        xr_new = step['xr_new']
        f_xl_old = step['f_xl_old']
        f_xr_old = step['f_xr_old']
        f_xl_new = step['f_xl_new']
        iteration = step['iteration']
        
        # 1. Касательная (метод Ньютона) в точке xl_old
        x_tan_left = max(0.7, xl_old - 0.4)
        x_tan_right = min(1.8, xl_old + 0.4)
        x_tan = np.linspace(x_tan_left, x_tan_right, 100)
        y_tan = f_xl_old + df(xl_old) * (x_tan - xl_old)
        plt.plot(x_tan, y_tan, '--', color=color, alpha=0.8, 
                linewidth=1.8, label=f'Итерация {iteration}: касательная')
        
        # Точка касания и её проекция на ось X
        plt.plot(xl_old, f_xl_old, 'o', color=color, markersize=8, alpha=0.9)
        plt.plot([xl_old, xl_old], [f_xl_old, 0], ':', color=color, alpha=0.6, linewidth=1)
        plt.plot(xl_new, 0, 'x', color=color, markersize=10, markeredgewidth=2.5, 
                label=f'Итерация {iteration}: xₙ (Ньютон)')
        
        # 2. Хорда между (xl_new, f(xl_new)) и (xr_old, f(xr_old))
        x1, y1 = xl_new, f_xl_new
        x2, y2 = xr_old, f_xr_old
        
        # Уравнение прямой хорды
        if abs(x2 - x1) > 1e-10:
            m = (y2 - y1) / (x2 - x1)
            x_chord_left = max(0.7, min(x1, x2) - 0.3)
            x_chord_right = min(1.8, max(x1, x2) + 0.3)
            x_chord = np.linspace(x_chord_left, x_chord_right, 100)
            y_chord = y1 + m * (x_chord - x1)
            plt.plot(x_chord, y_chord, '-.', color=color, alpha=0.85, 
                    linewidth=2, label=f'Итерация {iteration}: хорда')
            
            # Точки хорды и проекция x-пересечения
            plt.plot([x1, x2], [y1, y2], 'o', color=color, markersize=7, alpha=0.85)
            plt.plot([xr_new, xr_new], [0, min(y1, y2, 0) - 0.15], ':', 
                    color=color, alpha=0.6, linewidth=1)
            plt.plot(xr_new, 0, 'd', color=color, markersize=9, markeredgewidth=2,
                    label=f'Итерация {iteration}: xᵣ (хорда)')
    
    # Настройка графика
    plt.xlim(0.7, 1.8)
    plt.ylim(-1.5, 1.5)
    plt.xlabel('x', fontsize=12)
    plt.ylabel('f(x)', fontsize=12)
    plt.title('Комбинированный метод: касательные (Ньютон) и хорды', fontsize=14, fontweight='bold')
    plt.legend(loc='upper left', fontsize=9, ncol=2)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.show()
