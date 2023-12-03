import argparse

word_digits = {
    'one': 1,
    'two': 2,
    'three': 3,
    'four': 4,
    'five': 5,
    'six': 6,
    'seven': 7,
    'eight': 8,
    'nine': 9
}


def read_file(file: str):
    for line in open(file):
        yield line


def get_calibration_values(input: str, part_two: bool):
    """Returns a list of calibration values from the input"""

    calibration_values = []
    for line in read_file(input):
        # List of tuples (idx, value)
        pos_val = []
        if part_two:
            for key in word_digits.keys():
                #                pos = line.find(key, 0, len(line))
                #                if pos != -1:
                #                    pos_val.append(tuple((pos, word_digits[key])))
                #
                #                pos = line[::-1].find(key[::-1], 0, len(line))
                #                if pos != -1:
                #                   pos_val.append(tuple((len(line) - pos, word_digits[key])))
                pos = 0
                while True:
                    pos = line.find(key, pos, len(line))
                    if pos == -1:
                        break
                    pos_val.append(tuple((pos, word_digits[key])))
                    pos = pos + len(key) - 1

        for value in word_digits.values():
            #            pos = line.find(str(value), 0, len(line))
            #            if pos != -1:
            #                pos_val.append(tuple((pos, value)))
            #
            #            pos = line[::-1].find(str(value), 0, len(line))
            #            if pos != -1:
            #                pos_val.append(tuple((len(line) - pos, value)))
            pos = 0
            while True:
                pos = line.find(str(value), pos, len(line))
                if pos == -1:
                    break
                pos_val.append(tuple((pos, value)))
                pos = pos + 1

        # Sort the now populated list by the index
        pos_val.sort(key=lambda a: a[0])
        calibration_values.append(
            int(str(pos_val[0][1]) + str(pos_val[len(pos_val) - 1][1])))

    return calibration_values


if __name__ == '__main__':

    parser = argparse.ArgumentParser(prog='Day One AoC')
    parser.add_argument('-f', '--filename', type=str)
    parser.add_argument('-e',
                        '--extended',
                        type=bool,
                        action=argparse.BooleanOptionalAction)

    args = parser.parse_args()
    output_values = get_calibration_values(args.filename, args.extended)
    print(sum(output_values))
