#ifndef NONOGRAM_H
#define NONOGRAM_H

struct LineArrangements
{
    int numClues; 
    int *clues;
    int spacesToFill;
    int numArrangements;
    int *arrangements;
    
};

// Function to create all possible arrangements as a binary sequance (number) based on clues
void genLineArrangements(struct LineArrangements *line);
//function for comparing sequences using bitwise And or Nand depending on the desirable mode
int binaryComparison(int value, int binarySeq, int mode);
// Function for filtering matching arrangements by using binaryComparison
void filterLineArrangementsByBinarySeq(struct LineArrangements *line, int currentAxis, int mode);
// Function for checking all of the arrangements overlap
int checkLineOverlap(struct LineArrangements *line);

#endif
