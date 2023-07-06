#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int headerSize = 44;

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        fclose(input);
        printf("Input is not a WAV file.");
        return 1;
    }

    WAVHEADER *head = NULL;

    fread(head, sizeof(BYTE) * headerSize, 1, input);

    check_format(head);

    // Open output file for writing
    // TODO #5

    // Write header to file
    // TODO #6

    // Use get_block_size to calculate size of block
    // TODO #7

    // Write reversed audio to file
    // TODO #8
}

int check_format(WAVHEADER header)
{
    if(header[8] == 'W' && header[9] == 'A')
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return 0;
}