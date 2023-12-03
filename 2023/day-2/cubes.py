import argparse
import re
import functools


def read_file(input: str):
    for line in open(input):
        yield line


def is_valid_game(input_cubes, max_cubes):
    if not input_cubes:
        return False

    for max_cube in max_cubes:
        if max_cube[1] in input_cubes:
            if input_cubes[max_cube[1]] > max_cube[0]:
                return False
                break

    return True


def get_colour_max(cube_str: str) -> dict:

    cubes = re.findall(r'(\d+)\s(\w+)', cube_str)

    max_cubes = {}
    for cube in cubes:
        if cube[1] in max_cubes:
            max_cubes[cube[1]] = max(int(cube[0]), max_cubes[cube[1]])
        else:
            max_cubes[cube[1]] = int(cube[0])

    return max_cubes


def core(input: str, constraints: list, extended: bool):

    result = []
    game_id = 0
    for game in read_file(input):
        game_id += 1
        colours = get_colour_max(game)
        if not colours:
            continue

        if not extended:
            if is_valid_game(colours, constraints):
                result.append(game_id)
        else:
            # Use reduce to multiply each item
            result.append(
                functools.reduce((lambda x, y: x * y), colours.values()))

    return sum(result)


if __name__ == '__main__':

    parser = argparse.ArgumentParser(prog='Day Two AoC')
    parser.add_argument('-f', '--filename', type=str)
    parser.add_argument('-e',
                        '--extended',
                        type=bool,
                        action=argparse.BooleanOptionalAction)

    args = parser.parse_args()

    known_set = [((12, 'red')), ((13, 'green')), ((14, 'blue'))]

    answer = core(args.filename, known_set, args.extended)
    print(answer)
