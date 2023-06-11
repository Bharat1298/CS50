#include <stdio.h>
#include <cs50.h>

int collatz(int input);
int main(void){
    int input = get_int("Number: ");
    collatz(input);
}

int collatz(int input){
    if(input == 1){
        printf("%d\n", input);
        return 0;
    }
    if((input % 2) == 0){
        return collatz(input / 2);
    }else{
        return collatz(3 * input + 1);
    }
}