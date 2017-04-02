// Difficulty: 1.2

#include <stdio.h>

int main(){
    int fizzOn, buzzOn, numItems;
    scanf("%d %d %d",&fizzOn,&buzzOn,&numItems);
    for(int i = 1; i <= numItems; ++i){
        if(i % fizzOn == 0 && i % buzzOn == 0) puts("FizzBuzz");
        else if(i % fizzOn == 0) puts("Fizz");
        else if(i % buzzOn == 0) puts("Buzz");
        else printf("%d\n",i);
    }
}


