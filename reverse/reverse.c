#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == NULL){
        printf("Input is not a WAV file\n");
        fclose(input);
        return 1;
    }

    WAVHEADER head;

    fread(&head, sizeof(WAVHEADER), 1, input);

    if(!check_format(head)){
        printf("Invalid format\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");

    if(output == NULL){
        printf("Output file is invalid\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    fwrite(&head, sizeof(WAVHEADER), 1, output);

    int blockSize = get_block_size(head);

    BYTE buffer[blockSize];

    int size = head.subchunk2Size / blockSize;

    for(int i = 1; i <= size; i++){
        fseek(input, -blockSize * i, SEEK_END);
        fread(buffer, blockSize, 1, input);
        fwrite(buffer, blockSize, 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header)
{
    if(header.format[0] == 'W' && header.format[1] == 'A' &&
       header.format[2] == 'V' && header.format[3] == 'E'){
        return 1;
    }else{
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    return (header.bitsPerSample / 8) * header.numChannels;
}