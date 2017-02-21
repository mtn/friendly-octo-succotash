// Difficulty: 1.2

#include <stdio.h>

int main(){
    int expected_pieces[] = { 1,1,2,2,2,8 };
    int pieces[6];
    for(int i = 0; i < 6; ++i){
        scanf("%d",&pieces[i]);
        printf("%d ",expected_pieces[i]-pieces[i]);
    }
}
