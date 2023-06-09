#include <cs50.h>
#include <stdio.h>

int size;
int main(void)
{
    do{
        size = get_int("How big is the pyramid? ");
    }while(size < 1 || size > 8);

    int rowsLeft = size;

    for(int rows = 1; rows <= size; rows++){
        for(int space = rowsLeft - 1; space > 0; space--){
            printf(" ");
        }
        for(int left = 0; left < rows; left++){
            printf("#");
        }
        printf("  ");
        for(int left = 0; left < rows; left++){
            printf("#");
        }
        rowsLeft -= 1;
        printf("\n");
    }
}