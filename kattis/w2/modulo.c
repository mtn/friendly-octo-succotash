// Difficulty: 1.3

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(){
    bool *seen = malloc(sizeof(bool)*42);
    for(int i = 0; i < 42; ++i) seen[i] = false;
    int read, count=0;
    for(int i = 0; i < 10; ++i){
        scanf("%d",&read);
        if(!seen[read%42]){
            ++count;
            seen[read%42] = true;
        }
    }
    printf("%d",count);
    free(seen);
}
