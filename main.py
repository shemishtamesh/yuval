from line import LineArrangements

def main():
    one = LineArrangements([3,1,2], 10)
    one.filter_line_arrangements_by_binary_seq(1023, 0)
    one.filter_line_arrangements_by_binary_seq(1, 1)
    # for i in range(one.axis.numPossibleArrangements):
    #     print(one.axis.possibleArrangements[i])
    overlap = one.check_line_overlap()
    print(f"{overlap}")

main()