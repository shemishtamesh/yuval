#ifndef NONOGRAM_H
#define NONOGRAM_H

struct Axis
{
    int numClues;
    int *clues;
    int totalSpaces;
    int numPossibleArrangements;
    int *possibleArrangements;
    
};

void createAxisPossibleArrangements(struct Axis *axis);
void filterPossibilities(struct Axis *axis, int currentAxis);
int checkOverlap(struct Axis *axis);

#endif
