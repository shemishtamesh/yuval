#include "nonogram.h"

void genLineArrangements(struct LineArrangements *line){
    //initialize the segmentLengths array
    int spaceSegments = line->numClues + 1;
    int segmentLengths[spaceSegments];
    for(int segmentIndex = 0; segmentIndex < spaceSegments; segmentIndex++){
        segmentLengths[segmentIndex] = 0;
    }

    int totalSegmentLengths = 0;
    for(int arrangementIndex; arrangementIndex < line->numArrangements; arrangementIndex++){

        if(line->spacesToFill){ //if there are spaces to fill then
            int currentSegment = 0;
            do{ //create all segment arrays with a sum of spacesToFill
               if(segmentLengths[currentSegment] > line->spacesToFill){
                    segmentLengths[currentSegment] = 0;
                    totalSegmentLengths -= (line->spacesToFill + 1);
                    currentSegment++;
               } else{
                    currentSegment = 0;
               }
               segmentLengths[currentSegment]++;
               totalSegmentLengths++;
            } while(totalSegmentLengths != line->spacesToFill);
        }
        //calculate the binary form of a unique arrangement the array generated above
        int priorSegment = 0;
        for (int clueIndex = 0; clueIndex < line->numClues; clueIndex++){
            priorSegment += segmentLengths[clueIndex];
            line->arrangements[arrangementIndex] += ((1 << priorSegment) * ((1 << line->clues[clueIndex]) - 1));
            priorSegment += line->clues[clueIndex] + 1;
        }  
    }
}

int binaryComparison(int value, int binarySeq, int mode) {
    if (mode) {
        return value & binarySeq;
    } else {
        return -~value & binarySeq;
    }
} 

void filterLineArrangementsByBinarySeq(struct LineArrangements *line, int BinarySeq, int mode) {
    int newNumArrangements = 0;
    for (int arrangementIndex = 0; arrangementIndex < line->numArrangements; arrangementIndex++) {
        if (binaryComparison(line->arrangements[arrangementIndex], BinarySeq, mode)) {
            line->arrangements[newNumArrangements] = line->arrangements[arrangementIndex];
            newNumArrangements++;
        }
    }
    line->numArrangements = newNumArrangements;
}

int checkLineOverlap(struct LineArrangements *line, int mode){
    int overlap;
    if (mode){
        overlap = line->arrangements[0];
    } else{
        overlap = -~line->arrangements[0];
    }
    
    for (int arrangementIndex = 1; arrangementIndex < line->numArrangements; arrangementIndex++){
        overlap = binaryComparison(line->arrangements[arrangementIndex], overlap, mode);
    }
    return -~overlap;
}
