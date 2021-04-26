#include "diff.h"
#include <stdlib.h>

//a2 = a1 , copy a1 to a2 
void copyArray(int* a1, int* a2, int size) {
    for (int i = 0; i < size; i++) {
        a2[i] = a1[i];
    }
}

//Return a int range from 0~ (number-1)
int randomRange(int number) {
    return rand() % number;
}

//return a array from 0 ~ (length(-1) , but disarray them.
int* randomArrayIndex(int length) {
    int* randomIndex = new int[length];
    for (int i = 0; i < length; i++) {
        randomIndex[i] = i;
    }
    for (int i = 0; i < length; i++) {
        int swapI = randomRange(length);
        int swapI2 = randomRange(length);
        int temp = randomIndex[swapI];
        randomIndex[swapI] = randomIndex[swapI2];
        randomIndex[swapI2] = temp;
    }
    return randomIndex;
}