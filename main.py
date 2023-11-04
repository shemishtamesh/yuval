from line import LineArrangements


LINE_SIZE = 10


def main():
    one = LineArrangements([5], LINE_SIZE)
    # one.filter_line_arrangements_by_binary_seq(1, 0)

    # for i in range(one.line.numArrangements):
    #     print(one.line.arrangements[i])
    one.filter_line_arrangements_by_binary_seq(1, 1)
    overlap = one.check_line_overlap(0)
    print(f"{overlap}")

main()
