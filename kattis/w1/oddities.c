// Difficulty: 1.3

#include <stdio.h>

int main(){
    int numQueries;
    scanf("%d",&numQueries);

    int temp;
    for(int i = 0; i < numQueries; ++i){
        scanf("%d",&temp);
        if(temp%2==0)
            printf("%d is even\n",temp);
        else
            printf("%d is odd\n",temp);
    }
}
