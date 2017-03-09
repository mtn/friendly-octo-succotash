// Difficulty: 3.4

#include <stdio.h>

int main(){
    unsigned long numCuts, width, height;
    scanf("%lu",&numCuts);
    width = numCuts/2;
    height= numCuts-width;
    printf("%lu",(width + 1) * (height + 1));
}
