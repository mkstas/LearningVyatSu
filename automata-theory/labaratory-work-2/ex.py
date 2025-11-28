ROCK = 1      # Камень
PAPER = 2     # Бумага
SCISSORS = 3  # Ножницы

# history[0] — только ходы противника
history = [[], [], []]

def set_parameters(set_count: int, wins_per_set: int) -> None:
    pass

def on_game_start() -> None:
    history[0].clear()

def beat(move: int) -> int:
    """ Возвращает ход, который бьёт переданный """
    return {ROCK: PAPER, PAPER: SCISSORS, SCISSORS: ROCK}[move]

def choose(previous_opponent_choice: int) -> int:
    """
    Основная функция выбора хода.
    """
    # Первый ход игры
    if previous_opponent_choice == 0:
        return PAPER

    # Сохраняем текущий ход противника
    history[0].append(previous_opponent_choice)

    # Нужны минимум 3 хода в истории, чтобы анализировать последние два
    if len(history[0]) < 3:
        return PAPER

    # Последние два хода противника
    last_two = tuple(history[0][-2:])   # например (1, 3) — Камень → Ножницы

    # Ищем все случаи в истории, когда встречалась точно такая же пара подряд
    for i in range(len(history[0]) - 2):  # -2 потому что смотрим на следующий после пары
        if tuple(history[0][i:i+2]) == last_two:
            # Нашли паттерн! Смотрим, что противник играл сразу после этой пары
            next_move_after_pattern = history[0][i + 2]
            return beat(next_move_after_pattern)  # бьём предсказанный ход

    # Если ни одного совпадения не найдено — играем Бумагу
    return PAPER

def on_game_end() -> None:
    pass