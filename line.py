import ctypes
import math
import functools

# Load the shared library (replace 'nonogram.so' with the actual filename)
nonolib = ctypes.CDLL('./nonogram.so')

# Define a ctypes structure for Axis
class LineArrangementsStruct(ctypes.Structure):
    _fields_ = [
        ("numClues", ctypes.c_int),
        ("clues", ctypes.POINTER(ctypes.c_int)),
        ("spacesToFill", ctypes.c_int),
        ("numArrangements", ctypes.c_int),
        ("arrangements", ctypes.POINTER(ctypes.c_int))
    ]

class LineArrangements:
    def __init__(self, clues, line_size):
        spaces_to_fill = line_size - functools.reduce(lambda a, b: a + b + 1, clues)
        num_clues = len(clues)
        self.line = LineArrangementsStruct()
        self.initialize_line_arrangements(clues, num_clues, spaces_to_fill)

    def initialize_line_arrangements(self, clues, num_clues, spaces_to_fill):
        self.line.numClues = num_clues
        self.line.spacesToFill = spaces_to_fill
        self.line.clues = (ctypes.c_int * num_clues)(*clues)  # Create C array
        self.line.numArrangements = math.comb(spaces_to_fill + num_clues, spaces_to_fill)
        self.line.arrangements = (ctypes.c_int * self.line.numArrangements)()
        for i in range(self.line.numArrangements):
            self.line.arrangements[i] = 0
        nonolib.genLineArrangements(ctypes.byref(self.line))

    def filter_line_arrangements_by_binary_seq(self, binarySeq, mode):
        nonolib.filterLineArrangementsByBinarySeq(ctypes.byref(self.line), binarySeq, mode)
        new_arrangements = (ctypes.c_int * self.line.numArrangements)()
        #save the first 'numPossibleArrangements' - were modified in nonolib.filterPossibilities
        for i in range(self.line.numArrangements):
            new_arrangements[i] = self.line.arrangements[i]
        self.line.arrangements = new_arrangements


    def check_line_overlap(self, mode):
        return nonolib.checkLineOverlap(ctypes.byref(self.line), mode)


