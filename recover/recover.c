#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    BYTE Buffer[BLOCK_SIZE];
    int counter = 0;
    char* filename = malloc(8 * sizeof(char));
    char* oldFile = malloc(8 * sizeof(char));
    if(argc != 2){
        printf("Usage: ./recover IMAGE");
        free(filename);
        free(oldFile);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = NULL;
    FILE *oldFile = NULL;

    if(input == NULL){
        free(filename);
        free(oldFile);
        return 1;
    }

    while(fread(Buffer, sizeof(char), BLOCK_SIZE, input)){
        if(Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff
           && ((Buffer[3] & 0xf0) == 0xe0)){
              sprintf(filename, "%03i.jpg", counter);
              output = fopen(filename, "w");
              counter++;
            }
        if(output != NULL){
            if(!counter){
                fwrite(Buffer, BLOCK_SIZE, 1, output);
            }else{
                sprintf(oldFile, "%03i.jpg", counter - 1);
                oldFile = 
                fclose(oldFile);
                fwrite(Buffer, BLOCK_SIZE, 1, output);
            }
        }
    }

    fclose(output);
    free(filename);
    free(oldFile);
    fclose(input);

}