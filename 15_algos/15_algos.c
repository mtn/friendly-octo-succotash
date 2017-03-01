#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int* selectionSort(int arr[]){
    int sorted = 0, smallestInd = 0, temp;

    while(sorted < SIZE-1){
        for(int i = sorted; i < SIZE; ++i){
            if(arr[i] < arr[smallestInd])
                smallestInd = i;
        }
        temp = arr[sorted];
        arr[sorted] = arr[smallestInd];
        arr[smallestInd] = temp;

        ++sorted;
    }
    return arr;
}

int* insertionSort(int arr[]){
    int j, temp;
    for(int i = 1; i < SIZE; ++i){
        j = i;
        while(j > 0 && arr[j] < arr[j-1]){
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
            --j;
        }
    }
    return arr;
}

/* int* quickSort(int arr[]){ */
/*     return arr; */
/* } */

void printArr(int* arr){
    printf("[");
    for(int i = 0; i < SIZE-1; ++i)
        printf("%d,",arr[i]);
    printf("%d]\n",arr[SIZE-1]);
}

void reset(int randArr[], int toSort[]){
    for(int i = 0; i < SIZE; ++i)
        toSort[i] = randArr[i];
}

int main(){
    int randArr[SIZE], toSort[SIZE];
    for(int i = 0; i < SIZE; ++i)
        randArr[i] = rand() % 1000;

    puts("\nUnsorted array:");
    printArr(randArr);
    reset(randArr,toSort);

    puts("\nSelection sort:");
    printArr(selectionSort(toSort));
    reset(randArr,toSort);

    puts("\nInsertion sort:");
    printArr(insertionSort(toSort));
    reset(randArr,toSort);

    /* puts("\nQuicksort:"); */
    /* printArr(quickSort(toSort)); */
    /* reset(randArr,toSort); */
}

