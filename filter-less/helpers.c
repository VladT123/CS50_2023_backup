#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {

            //This line determines the average colour for each pixel.
            int average = round((image [i][j].rgbtBlue + image [i][j].rgbtGreen + image [i][j].rgbtRed) / 3.0);
            image [i][j].rgbtRed = average; //This line changes the current level of red to average.
            image [i][j].rgbtGreen = average; //This line changes the current level of green to average.
            image [i][j].rgbtBlue = average; //This line changes the current level of blue to average.
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //This line stores sepia changes to current level of red to sepia using formula from problem set.
            float SRed = round(0.393 * image [i][j].rgbtRed + 0.769 * image [i][j].rgbtGreen + 0.189 * image [i][j].rgbtBlue);
            //This line stores sepia changes to current level of green to sepia using formula from problem set.
            float Sgreen = round(0.349 * image [i][j].rgbtRed + 0.686 * image [i][j].rgbtGreen + 0.168 * image [i][j].rgbtBlue);
            //This line stores sepia changes to current level of blue to sepia using formula from problem set.
            float SBlue = round(0.272 * image [i][j].rgbtRed + 0.534 * image [i][j].rgbtGreen + 0.131 * image [i][j].rgbtBlue);
            //Lines bellow checks if the colour level for each colour is higher than max. And if the sepia colour is higher than the maximum of 255, set the current pixel colour to 255. Otherwise, puts sepia colour into the current pixel.

            if (SRed > 255)
            {
                image [i][j].rgbtRed = 255;
            }
            else
            {
                image [i][j].rgbtRed = SRed;
            }

            if (Sgreen > 255)
            {
                image [i][j].rgbtGreen = 255;
            }
            else
            {
                image [i][j].rgbtGreen = Sgreen;
            }

            if (SBlue > 255)
            {
                image [i][j].rgbtBlue = 255;
            }
            else
            {
                image [i][j].rgbtBlue = SBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {

        for (int j = width - 1, tmp = 0; j >= 0; j--, tmp++)
        {
            temp[i][tmp] = image[i][j]; //This line copies the original image into a temporal array, but stores each row of pixels backwards.
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j]; //This line copy changed the image to the original image.
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int itemp[] = {i - 1, i, i + 1};//This 2 arrays used to separate picture into smaller chunks of 3 by 3.
            int jtemp[] = {j - 1, j, j + 1};
            float tempR = 0;
            float tempG = 0;
            float tempB = 0;

            for (int row = 0; row < 3; row++)//This array allow us to scan this 3 by 3 chunks of pixels.
            {
                for (int col = 0; col < 3; col++)
                {
                    int Crow = itemp[row];
                    int Ccol = jtemp[col];
                    if (Crow >= 0 && Crow < height && Ccol >= 0 && Ccol < width)
                    {
                        RGBTRIPLE pict = image[Crow][Ccol];

                        tempR = tempR + pict.rgbtRed;
                        tempG = tempG + pict.rgbtGreen;
                        tempB = tempB + pict.rgbtBlue;
                        count++;

                    }
                }
            }
            temp[i][j].rgbtRed = round(tempR / count);
            temp[i][j].rgbtGreen = round(tempG / count);
            temp[i][j].rgbtBlue = round(tempB / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
