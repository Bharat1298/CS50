#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    BYTE Buffer[512];
    int BLOCK_SIZE = 512;
    if(argc != 2){
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        return 1;
    }

    while(fread(Buffer, BLOCK_SIZE, 1, input)){
        fwrite(Buffer, BLOCK_SIZE, 1, output)
    }

}