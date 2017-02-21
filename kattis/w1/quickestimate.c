// Difficulty: 1.5

#include <stdio.h>
#include <string.h>

int main(){
    char str[100];
    int numQueries;
    scanf("%d",&numQueries);

    for(int i = 0; i < numQueries; ++i){
        scanf("%s",str);
        printf("%lu\n",strlen(str));
    }

}
