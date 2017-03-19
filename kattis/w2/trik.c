// Difficulty: 1.3

#include <stdio.h>

int main(){
    char in[50];
    scanf("%s",in);
    int cups[3] = {1,0,0}, temp;

    for(int i = 0; in[i] != '\0'; ++i){
        if(in[i] == 'A'){
            temp = cups[0];
            cups[0] = cups[1];
            cups[1] = temp;
        }
        else if(in[i] == 'B'){
            temp = cups[1];
            cups[1] = cups[2];
            cups[2] = temp;
        }
        else if(in[i] == 'C'){
            temp = cups[0];
            cups[0] = cups[2];
            cups[2] = temp;
        }
    }

    int j;
    for(j = 0; j < 3; ++j) if(cups[j] == 1) break;
    printf("%d",j+1);
}
