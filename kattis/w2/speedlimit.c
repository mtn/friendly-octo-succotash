// Difficulty: 1.3

#include <stdio.h>

int main(){
    int numSteps,mph,timeSoFar=0,time,total=0;
    scanf("%d",&numSteps);
    while(numSteps != -1){
        for(int i = 0; i < numSteps; ++i){
            scanf("%d %d",&mph,&time);
            time = time - timeSoFar;
            total += time*mph;
            timeSoFar += time;
        }
        printf("%d miles\n",total);
        timeSoFar = 0, total=0;
        scanf("%d",&numSteps);
    }
}
