// Difficulty: 1.5

#include <stdio.h>
#include <stdlib.h>

int compare_function(const void *a,const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}

int findind(int n, int items,int* list){
    for(int i = 0; i < items; ++i)
        if(list[i] == n) return i;
    return -1;
}

int main(){
    int itemsPer, temp;
    scanf("%d",&itemsPer);
    while(1){
        int* list1 = malloc(itemsPer*sizeof(int));
        int* list1copy = malloc(itemsPer*sizeof(int));
        int* list2 = malloc(itemsPer*sizeof(int));
        int* list2copy = malloc(itemsPer*sizeof(int));
        for(int i = 0; i < itemsPer; ++i){
            scanf("%d",&temp);
            list1[i] = temp;
            list1copy[i] = temp;
        }
        for(int i = 0; i < itemsPer; ++i){
            scanf("%d",&temp);
            list2[i] = temp;
            list2copy[i] = temp;
        }
        //sort list1 copy
        qsort(list1copy,itemsPer,sizeof(int),compare_function);
        qsort(list2,itemsPer,sizeof(int),compare_function);
        qsort(list2copy,itemsPer,sizeof(int),compare_function);
        int ind;
        for(int i = 0; i < itemsPer; ++i){
            ind = findind(list1copy[i],itemsPer,list1);
            list2[ind] = list2copy[i];
        }
        printf("\n");
        for(int i = 0; i < itemsPer; ++i)
            printf("%d\n",list2[i]);
        scanf("%d",&itemsPer);
        if(itemsPer == 0) break;
    }
}

