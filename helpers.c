#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = temp;
        }
    }

    return;
}

BYTE mean (int height, int width, BYTE pixel[height][width], int x, int y);
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average[i][j].rgbtBlue = mean (height, width, image[height][width].rgbtBlue, i, j);
            average[i][j].rgbtRed = mean (height, width, image[height][width].rgbtRed, i, j);
            average[i][j].rgbtGreen = mean (height, width, image[height][width].rgbtGreen, i, j);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = average[i][j];
        }
    }
    return;
}
BYTE mean (int height, int width, BYTE pixel[height][width], int x, int y)
    {
        int total = 0;
        int divisor = 0;
        for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x+i >= 0 && x+i <= height && y+j>= 0 && y+j <= width);
                    {
                        total += *pixel[x+i][y+j]
                        divisor +=1;
                    }
                }
            }
        return total/divisor;
    }

int sobel (int height, int width, int pixel[height][width], int x, int y);
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE new_colour[height][width];
     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate Gx
            new_colour[i][j].rgbtRed = sobel (height, width, *image[height][width].rgbtRed, i, j);
            new_colour[i][j].rgbtGreen = sobel (height, width, image[height][width].rgbtGreen, i, j);
            new_colour[i][j].rgbtBlue = sobel (height, width, image[height][width].rgbtBlue, i, j);
        }
    }
    return;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_colour[i][j];
        }
    }
}
int sobel (int height, int width, int image[height][width], int i, int j)
{
    int Gx = (image[i-1][j+1] - image[i-1][j-1] + 2 * (image[i][j+1] - (image[i][j-1])) + image[i+1][j+1] - image[i+1][j-1]);
    int Gy = (image[i+1][j-1] - image[i-1][j-1] + 2 * (image[i+1][j] - (image[i-1][j])) + image[i+1][j+1] - image[i-1][j+1]);
    int difference = sqrt(pow (Gx, 2) + pow (Gy, 2));
    if (difference > 255)
    {
        difference = 255;
    }
    return difference;
}
 
