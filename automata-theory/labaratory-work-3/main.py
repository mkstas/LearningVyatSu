SHOT_RESULT_EMPTY: int = 0
SHOT_RESULT_DAMAGE: int = 2
SHOT_RESULT_KILL: int = 3

_my_map: list[list[int]] = []
_opponent_map: list[list[int]] = []
_shot_history: list[list[int]] = []

_ship_count: dict[int, int] = {1: 4, 2: 3, 3: 2, 4: 1}

_moves_for_4: list[tuple[int, int]] = []
_moves_for_3: list[tuple[int, int]] = []
_moves_for_2: list[tuple[int, int]] = []
_moves_for_1: list[tuple[int, int]] = []

_hunt_mode: bool = False
_last_hit: tuple[int, int] = (-1, -1)
_hit_list: list[tuple[int, int]] = []


def _initialize_move_arrays() -> None:
    global _moves_for_4, _moves_for_3, _moves_for_2, _moves_for_1

    _moves_for_4 = []
    for i in range(10):
        for j in range(10):
            if j + 3 < 10:
                _moves_for_4.append((i, j))
            if i + 3 < 10:
                _moves_for_4.append((i, j))
    _moves_for_4 = sorted(set(_moves_for_4))

    _moves_for_3 = []
    for i in range(10):
        for j in range(10):
            if j + 2 < 10:
                _moves_for_3.append((i, j))
            if i + 2 < 10:
                _moves_for_3.append((i, j))
    _moves_for_3 = sorted(set(_moves_for_3))

    _moves_for_2 = []
    for i in range(10):
        for j in range(10):
            if j + 1 < 10:
                _moves_for_2.append((i, j))
            if i + 1 < 10:
                _moves_for_2.append((i, j))
    _moves_for_2 = sorted(set(_moves_for_2))

    _moves_for_1 = [(i, j) for i in range(10) for j in range(10)]
    _moves_for_1.sort()


def _is_valid_coordinate(x: int, y: int) -> bool:
    return 0 <= x < 10 and 0 <= y < 10


def _can_shoot_at(x: int, y: int) -> bool:
    return _is_valid_coordinate(x, y) and _shot_history[x][y] == 0


def _remove_move_from_all_arrays(x: int, y: int) -> None:
    global _moves_for_4, _moves_for_3, _moves_for_2, _moves_for_1
    _moves_for_4 = [(i, j) for (i, j) in _moves_for_4 if not (i == x and j == y)]
    _moves_for_3 = [(i, j) for (i, j) in _moves_for_3 if not (i == x and j == y)]
    _moves_for_2 = [(i, j) for (i, j) in _moves_for_2 if not (i == x and j == y)]
    _moves_for_1 = [(i, j) for (i, j) in _moves_for_1 if not (i == x and j == y)]


def _get_best_strategic_move() -> tuple[int, int]:
    if _ship_count[4] > 0:
        for move in _moves_for_4:
            if _can_shoot_at(*move):
                return move
    if _ship_count[3] > 0:
        for move in _moves_for_3:
            if _can_shoot_at(*move):
                return move
    if _ship_count[2] > 0:
        for move in _moves_for_2:
            if _can_shoot_at(*move):
                return move
    if _ship_count[1] > 0:
        for move in _moves_for_1:
            if _can_shoot_at(*move):
                return move
    for i in range(10):
        for j in range(10):
            if _can_shoot_at(i, j):
                return i, j
    return 0, 0


def _hunt_finish_1() -> tuple[int, int]:
    last_hit = _hit_list[0]
    directions = [
        (last_hit[0] - 1, last_hit[1]),
        (last_hit[0], last_hit[1] + 1),
        (last_hit[0] + 1, last_hit[1]),
        (last_hit[0], last_hit[1] - 1)
    ]
    for d in directions:
        if _can_shoot_at(*d):
            return d
    global _hunt_mode
    _hunt_mode = False
    return _get_best_strategic_move()


def _hunt_finish_2() -> tuple[int, int]:
    first_hit = _hit_list[0]
    last_hit = _hit_list[-1]

    if first_hit[0] == last_hit[0]:
        dy = 1 if last_hit[1] > first_hit[1] else -1
        dx = 0
        next_cell = (last_hit[0], last_hit[1] + dy)
        if _can_shoot_at(*next_cell):
            return next_cell
        else:
            prev_cell = (first_hit[0], first_hit[1] - dy)
            if _can_shoot_at(*prev_cell):
                return prev_cell
    else:
        dx = 1 if last_hit[0] > first_hit[0] else -1
        dy = 0
        next_cell = (last_hit[0] + dx, last_hit[1])
        if _can_shoot_at(*next_cell):
            return next_cell
        else:
            prev_cell = (first_hit[0] - dx, first_hit[1])
            if _can_shoot_at(*prev_cell):
                return prev_cell

    global _hunt_mode
    _hunt_mode = False
    return _get_best_strategic_move()


def _mark_area_around_ship() -> None:
    if not _hit_list:
        return

    xs = [hit[0] for hit in _hit_list]
    ys = [hit[1] for hit in _hit_list]
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)

    for x in range(min_x - 1, max_x + 2):
        for y in range(min_y - 1, max_y + 2):
            if _is_valid_coordinate(x, y) and _shot_history[x][y] == 0:
                _shot_history[x][y] = 1
                _remove_move_from_all_arrays(x, y)


def _initialize_game_state() -> None:
    global _my_map, _opponent_map, _shot_history
    _my_map = [[0 for _ in range(10)] for _ in range(10)]
    _opponent_map = [[0 for _ in range(10)] for _ in range(10)]
    _shot_history = [[0 for _ in range(10)] for _ in range(10)]

    global _ship_count
    _ship_count = {1: 4, 2: 3, 3: 2, 4: 1}

    _initialize_move_arrays()

    global _hunt_mode, _hit_list
    _hunt_mode = False
    _hit_list = []


def _generate_fixed_map() -> None:
    global _my_map
    _my_map = [[0 for _ in range(10)] for _ in range(10)]

    _my_map[6][1] = 1
    _my_map[7][1] = 1
    _my_map[8][1] = 1
    _my_map[9][1] = 1

    _my_map[1][7] = 1
    _my_map[1][8] = 1
    _my_map[1][9] = 1

    _my_map[3][4] = 1
    _my_map[4][4] = 1
    _my_map[5][4] = 1

    _my_map[0][2] = 1
    _my_map[1][2] = 1

    _my_map[3][0] = 1
    _my_map[4][0] = 1

    _my_map[9][6] = 1
    _my_map[9][7] = 1

    _my_map[0][5] = 1
    _my_map[2][8] = 1
    _my_map[5][7] = 1
    _my_map[7][9] = 1


def _update_strategy(result_code: int) -> None:
    global _hunt_mode, _hit_list, _ship_count

    if result_code == SHOT_RESULT_DAMAGE:
        _hunt_mode = True
        _hit_list.append(_last_hit)
    elif result_code == SHOT_RESULT_KILL:
        _mark_area_around_ship()
        if _hit_list:
            xs = [h[0] for h in _hit_list]
            ys = [h[1] for h in _hit_list]
            ship_size = max(max(xs) - min(xs), max(ys) - min(ys)) + 1
            if 1 <= ship_size <= 4:
                _ship_count[ship_size] -= 1
        _hunt_mode = False
        _hit_list = []


def set_parameters(set_count: int) -> None:
    pass


def on_game_start() -> None:
    _initialize_game_state()


def on_set_start() -> None:
    global _shot_history, _hunt_mode, _hit_list, _ship_count
    _shot_history = [[0 for _ in range(10)] for _ in range(10)]
    _generate_fixed_map()
    _initialize_move_arrays()
    _hunt_mode = False
    _hit_list = []
    _ship_count = {1: 4, 2: 3, 3: 2, 4: 1}


def get_map() -> list[list[int]]:
    return _my_map


def shoot() -> tuple[int, int]:
    global _last_hit, _hunt_mode

    if _hunt_mode:
        if len(_hit_list) == 1:
            coords = _hunt_finish_1()
        else:
            coords = _hunt_finish_2()
    else:
        coords = _get_best_strategic_move()

    _last_hit = coords
    x, y = coords
    if _is_valid_coordinate(x, y):
        _shot_history[x][y] = 1
        _remove_move_from_all_arrays(x, y)

    return coords


def shot_result(result_code: int) -> None:
    _update_strategy(result_code)


def on_opponent_shot(cell: tuple[int, int]) -> None:
    x, y = cell
    if _is_valid_coordinate(x, y):
        _opponent_map[x][y] = 1


def on_set_end() -> None:
    pass


def on_game_end() -> None:
    pass
