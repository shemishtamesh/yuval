#include "nonogram.h"
#include <stdlib.h>
#include <stdio.h>
// Function to create possible binary arrangements based on clues
void createAxisPossibleArrangements(struct Axis *axis)
{

    int fillerCount = 0;
    int numFillers = axis->numClues + 1;
    int fillers[numFillers];
    for (int i = 0; i < numFillers; i++)
    {
        fillers[i] = 0;
    }

    for (int i = 0; i < axis->numPossibleArrangements; i++)
    {
        int spacesPrior = 0;
        int index = 0;
        if (axis->totalSpaces)
        {
            do
            {
                if (fillers[index] > axis->totalSpaces)
                {
                    fillers[index] = 0;
                    fillerCount -= (axis->totalSpaces + 1);
                    index++;
                }
                else
                {
                    index = 0;
                }
                fillers[index] += 1;
                fillerCount += 1;
            } while (fillerCount != axis->totalSpaces);
        }

        for (int j = 0; j < axis->numClues; j++)
        {
            spacesPrior += fillers[j];
            axis->possibleArrangements[i] += ((1 << spacesPrior) * ((1 << axis->clues[j]) - 1));
            spacesPrior += axis->clues[j] + 1;
        }
    }
}

// Function for bitwise AND comparing row possible arrangements with the current axis
void filterPossibilities(struct Axis *axis, int currentAxis)
{
    int newNumPossibleArrangements = 0;
    for (int i = 0; i < axis->numPossibleArrangements; i++)
    {
        if (axis->possibleArrangements[i] & currentAxis)
        {
            //shifts all of the fitting arranegmets to the left (making them the first values)
            axis->possibleArrangements[newNumPossibleArrangements] = axis->possibleArrangements[i];
            newNumPossibleArrangements++;
        }
    }
    //the first 'newNumPossibleArrangements' have been changed
    axis->numPossibleArrangements = newNumPossibleArrangements;
}

// Function for checking possibilities overlapping using bitwise AND
int checkOverlap(struct Axis *axis)
{
    int overlap = axis->possibleArrangements[0];
    for (int i = 1; i < axis->numPossibleArrangements; i++)
    {
        overlap = overlap & axis->possibleArrangements[i];
    }
    return overlap;
}
