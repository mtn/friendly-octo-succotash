// Difficulty: 2.6

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int numWords;
    scanf("%d",&numWords);
    char currLongest[80], working[80];
    while(numWords != 0){
        int maxVowel = 0;
        for(int i = 0; i < numWords; ++i){
            scanf("%s",working);
            int i = 0, vowelCount = 0;
            while(working[i] != '\0'  && working[i+1] != '\0'){
                switch(working[i]){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'y':
                        if(working[i+1] == working[i]){
                            vowelCount++;
                        }
                        break;
                }
                ++i;
            }
            /* printf("%d %s\n",vowelCount,working); */
            if(vowelCount >= maxVowel){
                maxVowel = vowelCount;
                strcpy(currLongest,working);
            }
        }
        printf("%s\n",currLongest);
        scanf("%d",&numWords);
    }
}

