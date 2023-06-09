#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char rotate(char letter, int modifier);
int main(int argc, string argv[])
{

    if(argc != 2){
        printf("Usage: ./caesar key\n");
        return 1;
    }else{
        for(int i = 0; i < strlen(argv[1]); i++){
            if(!(argv[1][i] < '9' || argv[1][i] < '0')){
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    int key = atoi(argv[1]);

    string phrase = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0; i < strlen(phrase); i++){
        rotate(phrase[i], key);
    }
    printf("\n");
}

char rotate(char letter, int modifier){
    int value = (int) letter;
    if(isalpha(value)){
        modifier %= 26;
        value += modifier;
        if(value > 'z'){
            value -= 26;
        }else if(letter > 'Z' && letter < 'a'){
            value -= 26;
        }
    }
    letter = value;
    printf("%c", letter);
    return letter;
}