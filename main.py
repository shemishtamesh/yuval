from axis import Axis

def main():
    one = Axis([3,1,2], 10)
    one.filter_possibilities(1023)
    overlap = one.check_overlap()
    print(f"{overlap}")

main()