// Difficulty: 1.3
//
#include <stdio.h>

int main(){
    int hr, min;
    scanf("%d %d",&hr,&min);

    if(min >= 45) min -= 45;
    else{
        if(hr > 0) --hr;
        else hr = 23;
        min = ((min-45)+60)%60;
    }
    printf("%d %d",hr,min);
}
