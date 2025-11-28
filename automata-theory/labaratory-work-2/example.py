ROCK = 1  # Камень
PAPER = 2  # Бумага
SCISSORS = 3  # Ножницы
 
def beats(a: int, b: int) -> bool:
    """Возвращает True, если a побеждает b."""
    return (
        (a == ROCK and b == SCISSORS)
        or (a == SCISSORS and b == PAPER)
        or (a == PAPER and b == ROCK)
    )
 
 
def counter(move: int) -> int:
    """Возвращает ход, побеждающий данный."""
    if move == ROCK:
        return PAPER
    elif move == PAPER:
        return SCISSORS
    elif move == SCISSORS:
        return ROCK
    else:
        return PAPER
 
game_data: list[list[int]] = [[], [], []]
current_strategy: str = "A"
loss_streak: int = 0
 
def set_parameters(set_count: int, wins_per_set: int) -> None:
    """
    Вызывается один раз перед началом игры.
    Передаёт параметры, с которыми запущен турнир.
 
    :param set_count: Максимальное количество сетов в игре
    :param wins_per_set: Требуемое количество побед в сете
    """
    pass
 
 
def on_game_start() -> None:
    """ Вызывается один раз в начале игры. """
    global game_data, current_strategy, loss_streak
    game_data = [[], [], []]
    current_strategy = "A"
    loss_streak = 0
 
def strategy_A(enemy_moves: list[int]) -> int:
    """Поиск повторяющихся паттернов противника."""
    n = 2
    if len(enemy_moves) <= n:
        return PAPER
    pattern = tuple(enemy_moves[-n:])
    for i in range(len(enemy_moves) - n - 1, -1, -1):
        if tuple(enemy_moves[i: i + n]) == pattern:
            predicted = enemy_moves[i + n]
            return counter(predicted)
    return PAPER
 
def strategy_B(game_data: list[list[int]]) -> int:
    """Модификация стратегии A: анализирует пары (enemy, bot)."""
    n = 2
    enemy_moves = game_data[0]
    bot_moves = game_data[1]
 
    if len(enemy_moves) <= n or len(bot_moves) <= n:
        return PAPER
    pattern = list(zip(enemy_moves[-n:], bot_moves[-n:]))
    for i in range(len(enemy_moves) - n - 1, -1, -1):
        past_pattern = list(zip(enemy_moves[i: i + n], bot_moves[i: i + n]))
        if past_pattern == pattern:
            predicted_enemy = enemy_moves[i + n]
            return counter(predicted_enemy)
    return SCISSORS
 
 
def choose(previous_opponent_choice: int) -> int:
    """
    Функция должна вернуть число от 1 до 3, соответствующее фигуре, которую выбрал бот
    (1 - Камень, 2 - Бумага, 3 - Ножницы).
 
    Передаваемый параметр previous_opponent_choice - число от 1 до 3, выбор противника на предыдущем ходу.
    Самый первый раз за игру, при первом вызове choose, previous_opponent_choice равен 0
    (т.к. предыдущих ходов ещё не было).
 
    :param previous_opponent_choice: Код фигуры, выбранной противником на предыдущем ходу
    :return: Код фигуры, которую выбирает бот
    """
    global game_data, current_strategy, loss_streak
 
    if previous_opponent_choice == 0:
        return PAPER
 
    game_data[0].append(previous_opponent_choice)
 
    previous_result = 0
    if len(game_data[1]) > 0:
        last_bot_move = game_data[1][-1]
        last_enemy_move = previous_opponent_choice
 
        if beats(last_enemy_move, last_bot_move):
            # Противник победил
            previous_result = -1
            loss_streak += 1
        elif beats(last_bot_move, last_enemy_move):
            # Бот победил
            previous_result = 1
            loss_streak = 0
        else:
            # Ничья
            previous_result = 0
            loss_streak = 0
 
        if len(game_data[2]) > 0:
            game_data[2][-1] = previous_result
 
    # при 5 поражениях подряд — смена стратегии
    if loss_streak >= 5:
        current_strategy = "B" if current_strategy == "A" else "A"
        loss_streak = 0
 
    # выбор хода
    if current_strategy == "A":
        move = strategy_A(game_data[0])
    else:
        move = strategy_B(game_data)
 
    # записываем ход бота (результат будет записан в следующем раунде)
    game_data[1].append(move)
    # Временная запись, будет обновлено в следующем раунде
    game_data[2].append(0)
 
    return move
 
 
def on_game_end() -> None:
    """ Вызывается один раз в конце игры. """
    pass
