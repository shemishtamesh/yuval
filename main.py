from line import LineArrangements

def main():
    one = LineArrangements([3,1,2], 10) 
    one.filter_line_arrangements_by_binary_seq(5, 0)

    # for i in range(one.line.numArrangements):
    #     print(one.line.arrangements[i])
    overlap = one.check_line_overlap(0)
    print(f"{overlap}")

main()