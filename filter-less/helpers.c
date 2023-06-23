#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE originalRed;
    BYTE originalGreen;
    BYTE originalBlue;
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if(sepiaRed > 255){
                image[i][j].rgbtRed = 255;
            }else{
                image[i][j].rgbtRed = sepiaRed;
            }

            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if(sepiaGreen > 255){
                image[i][j].rgbtGreen = 255;
            }
            else{
                image[i][j].rgbtGreen = sepiaGreen;
            }

            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if(sepiaBlue > 255){
                image[i][j].rgbtBlue = 255;
            }
            else{
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
