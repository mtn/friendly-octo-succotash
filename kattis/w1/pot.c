// Difficulty: 1.2

#include <stdio.h>
#include <math.h>

int main(){
    int num_addends;
    scanf("%d",&num_addends);

    int temp,output = 0;
    for(int i = 0; i < num_addends; ++i){
        scanf("%d",&temp);
        output += (int)pow(temp/10,temp%10);
    }

    printf("%d",output);
}
