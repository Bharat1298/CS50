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
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
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
    RGBTRIPLE temp[width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){
            temp[j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp[i][j] = image[i][j];
        }
    }

    RGBTRIPLE topLeft, topMid, topRight, midLeft, mid, midRight, botLeft, botMid, botRight;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            topLeft =   temp[i - 1][j - 1];
            topMid =    temp[i - 1][j];
            topRight =  temp[i - 1][j + 1];
            midLeft =   temp[i][j - 1];
            mid =       temp[i][j];
            midRight =  temp[i][j + 1];
            botLeft =   temp[i + 1][j - 1];
            botMid =    temp[i + 1][j];
            botRight =  temp[i + 1][j + 1];
            if(i != 0 && i != height - 1 && j != 0 && j != width - 1){ //Middle Pixels
                image[i][j].rgbtRed = round((topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed
                                    + midLeft.rgbtRed + mid.rgbtRed + midRight.rgbtRed
                                    + botLeft.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 9.0);
                image[i][j].rgbtGreen = round((topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen
                                    + midLeft.rgbtGreen + mid.rgbtGreen + midRight.rgbtGreen
                                    + botLeft.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = round((topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue
                                    + midLeft.rgbtBlue + mid.rgbtBlue + midRight.rgbtBlue
                                    + botLeft.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 9.0);
            }else if(i == 0 && (j != 0 && j != width - 1)){ //Top Middle Pixels
                image[i][j].rgbtRed = round((midLeft.rgbtRed + mid.rgbtRed + midRight.rgbtRed
                                    + botLeft.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((midLeft.rgbtGreen + mid.rgbtGreen + midRight.rgbtGreen
                                    + botLeft.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((midLeft.rgbtBlue + mid.rgbtBlue + midRight.rgbtBlue
                                    + botLeft.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 6.0);
            }else if(i == height - 1 && (j != 0 && j != width - 1)){ //Bottom Middle Pixels
                image[i][j].rgbtRed = round((topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed
                                    + midLeft.rgbtRed + mid.rgbtRed + midRight.rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen
                                    + midLeft.rgbtGreen + mid.rgbtGreen + midRight.rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue
                                    + midLeft.rgbtBlue + mid.rgbtBlue + midRight.rgbtBlue) / 6.0);
            }else if(j == 0 && (i != 0 && i != height - 1)){ //Left Middle Pixels
                image[i][j].rgbtRed = round((topMid.rgbtRed + topRight.rgbtRed
                                    + mid.rgbtRed + midRight.rgbtRed
                                    + botMid.rgbtRed + botRight.rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((topMid.rgbtGreen + topRight.rgbtGreen
                                    + mid.rgbtGreen + midRight.rgbtGreen
                                    + botMid.rgbtGreen + botRight.rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((topMid.rgbtBlue + topRight.rgbtBlue
                                    + mid.rgbtBlue + midRight.rgbtBlue
                                    + botMid.rgbtBlue + botRight.rgbtBlue) / 6.0);
            }else if(j == width - 1 && (i != 0 && i != height - 1)){ //Right Middle Pixels
                image[i][j].rgbtRed = round((topLeft.rgbtRed + topMid.rgbtRed
                                    + midLeft.rgbtRed + mid.rgbtRed
                                    + botLeft.rgbtRed + botMid.rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((topLeft.rgbtGreen + topMid.rgbtGreen
                                    + midLeft.rgbtGreen + mid.rgbtGreen
                                    + botLeft.rgbtGreen + botMid.rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((topLeft.rgbtBlue + topMid.rgbtBlue
                                    + midLeft.rgbtBlue + mid.rgbtBlue
                                    + botLeft.rgbtBlue + botMid.rgbtBlue) / 6.0);
            }else if(i == 0 && j == 0){ //Top Left Corner
                image[i][j].rgbtRed = round((mid.rgbtRed + midRight.rgbtRed
                                    + botMid.rgbtRed + botRight.rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((mid.rgbtGreen + midRight.rgbtGreen
                                    + botMid.rgbtGreen + botRight.rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((mid.rgbtBlue + midRight.rgbtBlue
                                    + botMid.rgbtBlue + botRight.rgbtBlue) / 4.0);
            }else if(i == 0 && j == width - 1){ //Top Right Corner
                image[i][j].rgbtRed = round((midLeft.rgbtRed + mid.rgbtRed
                                    + botLeft.rgbtRed + botMid.rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((midLeft.rgbtGreen + mid.rgbtGreen
                                    + botLeft.rgbtGreen + botMid.rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((midLeft.rgbtBlue + mid.rgbtBlue
                                    + botLeft.rgbtBlue + botMid.rgbtBlue) / 4.0);
            }else if(i == height - 1 && j == 0){ //Bottom Left Corner
                image[i][j].rgbtRed = round((topMid.rgbtRed + topRight.rgbtRed
                                    + mid.rgbtRed + midRight.rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((topMid.rgbtGreen + topRight.rgbtGreen
                                    + mid.rgbtGreen + midRight.rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((topMid.rgbtBlue + topRight.rgbtBlue
                                    + mid.rgbtBlue + midRight.rgbtBlue) / 4.0);
            }else{ //Bottom Right
                image[i][j].rgbtRed = round((topLeft.rgbtRed + topMid.rgbtRed
                                    + midLeft.rgbtRed + mid.rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((topLeft.rgbtGreen + topMid.rgbtGreen
                                    + midLeft.rgbtGreen + mid.rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((topLeft.rgbtBlue + topMid.rgbtBlue
                                    + midLeft.rgbtBlue + mid.rgbtBlue) / 4.0);
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //sqrt(x^2 + y^2)
    return;
}
