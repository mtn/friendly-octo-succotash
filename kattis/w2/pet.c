// Difficulty: 1.3
//
#include <stdio.h>

int main(){
    int max=0, maxId=0, s1, s2, s3, s4;
    for(int i = 0; i < 5; ++i){
        scanf("%d %d %d %d",&s1,&s2,&s3,&s4);
        if(s1+s2+s3+s4 > max){
            max = s1+s2+s3+s4;
            maxId=i+1;
        }
    }
    printf("%d %d",maxId,max);
}
