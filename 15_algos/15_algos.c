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

int partition(int a[], int lo, int hi){
   int pivot, i, j, temp;
   pivot = a[lo];
   i = lo; j = hi;

   while(i < j){
        while(a[i] < pivot && hi > i) ++i;
        while(a[j] > pivot) --j;
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
   }

   temp = a[lo];
   a[lo] = a[j];
   a[j] = temp;
   return j;
}

void quickHelper(int a[], int lo, int hi){
   if(lo < hi) {
       int j = partition(a,lo,hi);
       quickHelper(a,lo,j-1);
       quickHelper(a,j+1,hi);
   }
}

void quickSort(int arr[]){
    quickHelper(arr,0,99);
}

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

    puts("\nQuicksort:");
    quickSort(toSort);
    printArr(toSort);
    reset(randArr,toSort);
}

