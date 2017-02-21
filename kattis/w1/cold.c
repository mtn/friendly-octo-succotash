// Difficulty: 1.2

#include <stdio.h>

int main(){
    int num_queries;
    scanf("%d",&num_queries);

    int count = 0, temp;
    for(int i = 0; i < num_queries; ++i){
        scanf("%d",&temp);
        if(temp < 0)
            ++count;
    }
    printf("%d",count);
}
