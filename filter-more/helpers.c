#include "helpers.h"
#include <math.h>

RGBTRIPLE matrix(RGBTRIPLE tl, RGBTRIPLE tm, RGBTRIPLE tr, RGBTRIPLE ml, RGBTRIPLE m, RGBTRIPLE mr,
           RGBTRIPLE bl, RGBTRIPLE bm, RGBTRIPLE br);

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
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp[i][j] = image[i][j];
        }
    }

    RGBTRIPLE topLeft, topMid, topRight, midLeft, mid, midRight, botLeft, botMid, botRight, zero;

    zero.rgbtRed = zero.rgbtGreen = zero.rgbtBlue = 0;

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
                image[i][j] = matrix(topLeft, topMid, topRight, midLeft, mid, midRight, botLeft, botMid, botRight);
            }else if(i == 0 && (j != 0 && j != width - 1)){ //Top Middle Pixels
                image[i][j] = matrix(zero, zero, zero, midLeft, mid, midRight, botLeft, botMid, botRight);
            }else if(i == height - 1 && (j != 0 && j != width - 1)){ //Bottom Middle Pixels
                image[i][j] = matrix(topLeft, topMid, topRight, midLeft, mid, midRight, zero, zero, zero);
            }else if(j == 0 && (i != 0 && i != height - 1)){ //Left Middle Pixels
                image[i][j] = matrix(zero, topMid, topRight, zero, mid, midRight, zero, botMid, botRight);
            }else if(j == width - 1 && (i != 0 && i != height - 1)){ //Right Middle Pixels
                image[i][j] = matrix(topLeft, topMid, zero, midLeft, mid, zero, botLeft, botMid, zero);
            }else if(i == 0 && j == 0){ //Top Left Corner
                image[i][j] = matrix(zero, zero, zero, zero, mid, midRight, zero, botMid, botRight);
            }else if(i == 0 && j == width - 1){ //Top Right Corner
                image[i][j] = matrix(zero, zero, zero, midLeft, mid, zero, botLeft, botMid, zero);
            }else if(i == height - 1 && j == 0){ //Bottom Left Corner
                image[i][j] = matrix(zero, topMid, topRight, zero, mid, midRight, zero, zero, zero);
            }else{ //Bottom Right
                image[i][j] = matrix(topLeft, topMid, zero, midLeft, mid, zero, zero, zero, zero);
            }
        }
    }

    return;
}


RGBTRIPLE matrix(RGBTRIPLE tl, RGBTRIPLE tm, RGBTRIPLE tr, RGBTRIPLE ml, RGBTRIPLE m, RGBTRIPLE mr,
           RGBTRIPLE bl, RGBTRIPLE bm, RGBTRIPLE br){
    RGBTRIPLE pixel;
    int xred, xgreen, xblue;
    int yred, ygreen, yblue;
    int avgRed, avgGreen, avgBlue;

    xred = (tl.rgbtRed * -1) + ( tm.rgbtRed * 0) + ( tr.rgbtRed * 1) +
           (ml.rgbtRed * -2) + ( m.rgbtRed * 0) + ( mr.rgbtRed * 2) +
           (bl.rgbtRed * -1) + ( bm.rgbtRed * 0) + ( br.rgbtRed * 1);

    xgreen = (tl.rgbtGreen * -1) + ( tm.rgbtGreen * 0) + ( tr.rgbtGreen * 1) +
           (ml.rgbtGreen * -2) + ( m.rgbtGreen * 0) + ( mr.rgbtGreen * 2) +
           (bl.rgbtGreen * -1) + ( bm.rgbtGreen * 0) + ( br.rgbtGreen * 1);

    xblue = (tl.rgbtBlue * -1) + ( tm.rgbtBlue * 0) + ( tr.rgbtBlue * 1) +
           (ml.rgbtBlue * -2) + ( m.rgbtBlue * 0) + ( mr.rgbtBlue * 2) +
           (bl.rgbtBlue * -1) + ( bm.rgbtBlue * 0) + ( br.rgbtBlue * 1);

    yred = (tl.rgbtRed * -1) + ( tm.rgbtRed * -2) + ( tr.rgbtRed * -1) +
           (ml.rgbtRed * 0) + ( m.rgbtRed * 0) + ( mr.rgbtRed * 0) +
           (bl.rgbtRed * 1) + ( bm.rgbtRed * 2) + ( br.rgbtRed * 1);

    ygreen = (tl.rgbtGreen * -1) + ( tm.rgbtGreen * -2) + ( tr.rgbtGreen * -1) +
           (ml.rgbtGreen * 0) + ( m.rgbtGreen * 0) + ( mr.rgbtGreen * 0) +
           (bl.rgbtGreen * 1) + ( bm.rgbtGreen * 2) + ( br.rgbtGreen * 1);

    yblue = (tl.rgbtBlue * -1) + ( tm.rgbtBlue * -2) + ( tr.rgbtBlue * -1) +
           (ml.rgbtBlue * 0) + ( m.rgbtBlue * 0) + ( mr.rgbtBlue * 0) +
           (bl.rgbtBlue * 1) + ( bm.rgbtBlue * 2) + ( br.rgbtBlue * 1);

    avgRed = round(sqrt((xred * xred) + (yred * yred)));

    if(avgRed > 255){
        avgRed = 255;
    }

    avgGreen = round(sqrt((xgreen * xgreen) + (ygreen * ygreen)));

    if(avgGreen > 255){
        avgGreen = 255;
    }

    avgBlue = round(sqrt((xblue * xblue) + (yblue * yblue)));

    if(avgBlue > 255){
        avgBlue = 255;
    }

    pixel.rgbtRed = avgRed;
    pixel.rgbtGreen = avgGreen;
    pixel.rgbtBlue = avgBlue;

    return pixel;
}