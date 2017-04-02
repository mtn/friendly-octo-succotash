// Difficulty: 1.9

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double dist(float x1, float y1, float x2, float y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

typedef struct {
    float x;
    float y;
} Pair;

int main(){
    int numTrials;
    float distFight;
    scanf("%f %d",&distFight,&numTrials);
    while(distFight != 0.0 && numTrials != 0){
        float xRead, yRead;
        Pair *arr = malloc(sizeof(Pair)*numTrials);
        for(int i = 0; i < numTrials; ++i){
            scanf("%f %f",&xRead,&yRead);
            arr[i].x = xRead;
            arr[i].y = yRead;
        }
        int *sweetOr = calloc(numTrials,sizeof(int));
        for(int i = 0; i < numTrials; ++i){
            for(int j = i; j < numTrials; ++j){
                if(i != j){
                    if(dist(arr[i].x,arr[i].y,arr[j].x,arr[j].y) <= distFight){
                        sweetOr[i] = 1;
                        sweetOr[j] = 1;
                    }
                }
            }
        }
        int sweetCount = 0;
        for(int i = 0; i < numTrials; ++i){
            if(!sweetOr[i]) sweetCount++;
        }
        printf("%d sour, %d sweet\n",numTrials-sweetCount,sweetCount);
        scanf("%f %d",&distFight,&numTrials);
    }
}

