#include <stdio.h>
#include <cs50.h>
#include <string.h>
// #include <stdbool.h>

int main(void){
    string string = get_string("String: ");
    int length = strlen(string);
    _Bool ordered = false;

    for(int i = 0; i < length; i++){
        if (string[i] == string[i -1] + 1){
            ordered = true;
        }else{
            ordered = false;
            return 0;
        }
    }
    if(ordered){
        printf("True\n");
    }else{
        printf("False\n");
    }

}