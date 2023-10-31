#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void arrayInitialize(int * array, int arraySize, int value){
    for(int i = 0; i < arraySize; i++){
        array[i] = value;
    }
    return;
}

int arraySum(int * array, int arraySize, int additional){
    int sum = 0; 
    for(int i = 0; i < arraySize; i++){
        sum += array[i] + additional;
    }
    return sum;
}

int calcNumArrangements(int numClues, int totalFillers){
    int NumArrangements = (int) (tgamma(totalFillers + numClues + 1) / (tgamma(totalFillers + 1) * tgamma(numClues + 1)));
    printf("there are %d possible arrengments \n", NumArrangements);
    return NumArrangements;
}

void createSpacing(int * fillers, int numFillers, int totalFillers){
    int index = 0;
    do{
        if(fillers[index] > totalFillers){
            fillers[index] = 0;
            index++;
        }
        else{
            index = 0;
        }
        fillers[index] += 1;
    }
    while (arraySum(fillers, numFillers, 0) != totalFillers);
    return;
}

void createAxisPossibleArrangements(int * arrangements, int * clues, int numClues, int totalFillers, int numArrangements){
    int numFillers = numClues + 1;
    int fillers[numFillers];
    arrayInitialize(fillers, numFillers, 0);
    int spacesPrior;
    for(int i = 0; i < numArrangements; i++){
        createSpacing(fillers, numFillers, totalFillers);
        spacesPrior = 0;
        for(int j = 0; j < numClues; j++){ 
            spacesPrior += fillers[j];
            arrangements[i] += (pow(2, spacesPrior))*(pow(2, clues[j]) - 1); 
            spacesPrior += clues[j] + 1;
        }
    }
}

int main() {
    int axisSize = 10;
    int clues[3] = {3, 1, 2};
    int numClues = sizeof(clues)/sizeof(int);
    int totalFillers = axisSize - arraySum(clues, numClues, 1) + 1;
    int numArrangements = calcNumArrangements(numClues, totalFillers);
    int *arrangements = (int*)malloc(numArrangements*4); 
    if (arrangements == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0);
    }
    arrayInitialize(arrangements, numArrangements, 0);
    createAxisPossibleArrangements(arrangements, clues, numClues, totalFillers, numArrangements);
    printf("their binary form are:\n");
    for(int i = 0; i < 10; i++){
        printf("%d \t", arrangements[i]);
    }    
}
