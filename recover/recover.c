#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    BYTE Buffer[512];
    if(argc != 2){
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        return 1;
    }

    while(fread(Buffer, BLOCK_SIZE, 1, input)){
        if(Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff
           && (Buffer[3] & 0xe == 0xe0))
    }

}