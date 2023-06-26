#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    BYTE Buffer[BLOCK_SIZE];
    int counter = 0;
    char* filename = malloc(8);
    if(argc != 2){
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        free(filename);
        return 1;
    }

    while(fread(Buffer, BLOCK_SIZE, 1, input)){
        if(Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff
           && ((Buffer[3] & 0xf0) == 0xe0)){
              sprintf(filename, "%03i.jpg", counter);
              FILE *output = fopen(filename, "W");
              if(counter == 0){
                  fwrite(Buffer, BLOCK_SIZE, 1, output);
                  counter++;
              }else{
                  fclose(output);
                  fwrite(Buffer, BLOCK_SIZE, 1, output);
                  counter++;
              }
              fclose(output);
           }
    }

    free(filename);
    fclose(input);

}