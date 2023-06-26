#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE BLOCK_SIZE;
    if(argc != 2){
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        return 1;
    }

    
}