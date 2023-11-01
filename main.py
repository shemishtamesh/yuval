import ctypes
import math
import functools

# Load the shared library (replace 'nonogram.so' with the actual filename)
nonolib = ctypes.CDLL('./nonogram.so')

# Define a ctypes structure for Axis
class AxisStruct(ctypes.Structure):
    _fields_ = [
        ("numClues", ctypes.c_int),
        ("clues", ctypes.POINTER(ctypes.c_int)),
        ("totalSpaces", ctypes.c_int),
        ("numPossibleArrangements", ctypes.c_int),
        ("possibleArrangements", ctypes.POINTER(ctypes.c_int))
    ]

class Axis:
    def __init__(self, clues, axis_size):
        total_spaces = axis_size - functools.reduce(lambda a, b: a + b + 1, clues) 
        num_clues = len(clues)
        self.axis = AxisStruct()
        self.initialize_axis(clues, num_clues, total_spaces)

    def initialize_axis(self, clues, num_clues, total_spaces):
        self.axis.numClues = num_clues
        self.axis.totalSpaces = total_spaces
        self.axis.clues = (ctypes.c_int * num_clues)(*clues)  # Create C array
        self.axis.numPossibleArrangements = math.comb(total_spaces + num_clues, total_spaces)
        self.axis.possibleArrangements = (ctypes.c_int * self.axis.numPossibleArrangements)()
        ctypes.cdll.msvcrt.memset(self.axis.possibleArrangements, 0, ctypes.sizeof(self.axis.possibleArrangements.contents))
        nonolib.createAxisPossibleArrangements(ctypes.byref(self.axis))
        
    def filter_possibilities(self, current_axis):
        nonolib.filterPossibilities(ctypes.byref(self.axis), current_axis)

    def check_overlap(self):
        return nonolib.checkOverlap(ctypes.byref(self.axis))

def main():
    one = Axis([9], 10)
    overlap = one.check_overlap()
    print(f"{overlap}")
    # for i in range(one.axis.numPossibleArrangements):
    #     print(one.axis.possibleArrangements[i])

main()
