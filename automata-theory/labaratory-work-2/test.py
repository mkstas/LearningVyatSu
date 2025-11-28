# test_bot.py
import random
from main import choose, beat  # Импортируем всё из твоего bot.py

# =============================================
# Простые тестовые противники
# =============================================

def random_bot(prev):
    """Случайный ход"""
    return random.choice([ROCK, PAPER, SCISSORS])

def fixed_bot(prev):
    """Всегда играет одно и то же — Камень"""
    return ROCK

def cycle_bot(prev):
    """Цикл: Камень → Бумага → Ножницы → Камень → ..."""
    moves = [ROCK, PAPER, SCISSORS]
    if not hasattr(cycle_bot, "idx"):
        cycle_bot.idx = 0
    move = moves[cycle_bot.idx]
    cycle_bot.idx = (cycle_bot.idx + 1) % 3
    return move

def repeat_last_bot(prev):
    """Повторяет свой предыдущий ход (на первый — Бумага)"""
    if prev == 0:
        return PAPER
    return prev

def anti_previous_bot(prev):
    """Контр-ход против предыдущего хода противника (то есть против нас)"""
    if prev == 0:
        return SCISSORS  # слабый старт, но ладно
    return beat(prev)

def pattern_bot(prev):
    """Играет по фиксированному паттерну: Бумага, Ножницы, Камень, Бумага, Ножницы, Камень..."""
    moves = [PAPER, SCISSORS, ROCK]
    if not hasattr(pattern_bot, "idx"):
        pattern_bot.idx = 0
    move = moves[pattern_bot.idx % 3]
    pattern_bot.idx += 1
    return move

# =============================================
# Симуляция одной игры (100 раундов)
# =============================================

def play_game(opponent_func, games_count=100, verbose=False):
    wins = 0
    losses = 0
    draws = 0

    # Сбрасываем историю бота
    history[0].clear()
    history[1].clear()
    history[2].clear()

    prev_opp = 0  # первый ход

    for move_num in range(games_count):
        my_move = choose(prev_opp)
        opp_move = opponent_func(prev_opp)

        # Сохраняем в историю противника (как делает настоящая система)
        if prev_opp != 0:
            history[0].append(prev_opp)

        if my_move == opp_move:
            draws += 1
            result = "Ничья"
        elif beat(my_move) == opp_move:
            wins += 1
            result = "Победа"
        else:
            losses += 1
            result = "Поражение"

        if verbose and move_num < 20:  # первые 20 ходов подробно
            names = {1: "Камень", 2: "Бумага", 3: "Ножницы"}
            print(f"Ход {move_num+1:2d}: Я — {names[my_move]}, Противник — {names[opp_move]} → {result}")

        prev_opp = opp_move  # для следующего хода

    winrate = wins / games_count * 100
    print(f"\nПротив {opponent_func.__name__}: "
          f"Побед: {wins}, Поражений: {losses}, Ничьих: {draws} → Винрейт: {winrate:.1f}%")
    return wins, losses, draws

# =============================================
# Запуск тестов
# =============================================

if __name__ == "__main__":
    print("Тестируем твоего бота!\n")

    opponents = [
        random_bot,
        fixed_bot,
        cycle_bot,
        repeat_last_bot,
        anti_previous_bot,
        pattern_bot,
    ]

    total_wins = 0
    total_games = 0

    for opp in opponents:
        w, l, d = play_game(opp, games_count=200, verbose=(opp is pattern_bot))
        total_wins += w
        total_games += 200

    print("\n" + "="*50)
    print(f"ИТОГО: Винрейт против всех ботов: {total_wins / total_games * 100:.1f}%")
    print("="*50)
