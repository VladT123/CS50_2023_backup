#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<=height; i++)
    {
        for (int j=0;j<=width;j++)
        {


            int average =round((image [i][j].rgbtBlue + image [i][j].rgbtGreen + image [i][j].rgbtRed)/3.0);
            image [i][j].rgbtRed=average;
            image [i][j].rgbtGreen=average;
            image [i][j].rgbtBlue=average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half=width/2;
    RGBTRIPLE temp[height][width];

    for (int i=0; i<height; i++)
    {

        for (int j=width-1,tmp=0; j>=0;j--,tmp++)
        {
            temp[i][tmp]=image[i][j];
        }
    }
    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width;j++)
        {
            image[i][j]= temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
RGBTRIPLE temp[height][width];
for (int i=0; i<height; i++)
    {
        for (int j=0;j<width;j++)
        {
            int count =0;
            int itemp[]= {i-1, i ,i+1};
            int jtemp[]= {j-1, j ,j+1};
            float tempR=0;
            float tempG=0;
            float tempB=0;

            for (int row=0; row<3; row++)
            {
                for (int col=0; col<3; col++)
                {
                    int Crow = itemp[row];
                    int Ccol = jtemp[col];
                    if(Crow>=0 && Crow < height && Ccol>=0 && Ccol < width)
                    {
                        RGBTRIPLE pict=image[Crow][Ccol];

                        tempR=tempR+pict.rgbtRed;
                        tempG=tempG+pict.rgbtGreen;
                        tempB=tempB+pict.rgbtBlue;
                        count++;

                    }
                }
            }
            temp[i][j].rgbtRed=round(tempR/count);
            temp[i][j].rgbtGreen=round(tempG/count);
            temp[i][j].rgbtBlue=round(tempB/count);
        }
    }
for (int i=0; i<height; i++)
    {
        for (int j=0;j<width;j++)
        {
            image[i][j]= temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int Gx[3][3] =
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };
    int Gy[3][3] =
    {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

for (int i=0; i<height; i++)
    {
        for (int j=0;j<width;j++)
        {
            int itemp[]= {i-1, i ,i+1};
            int jtemp[]= {j-1, j ,j+1};
            float GxR=0;
            float GxG=0;
            float GxB=0;
            float GyR=0;
            float GyG=0;
            float GyB=0;

            for (int row=0; row<3; row++)
            {
                for (int col=0; col<3; col++)
                {
                    int Crow = itemp[row];
                    int Ccol = jtemp[col];
                    if(Crow>=0 && Crow < height && Ccol>=0 && Ccol < width)
                    {
                        RGBTRIPLE pict=image[Crow][Ccol];

                        GxR+=Gx[row][col]*pict.rgbtRed;
                        GxG+=Gx[row][col]*pict.rgbtGreen;
                        GxB+=Gx[row][col]*pict.rgbtBlue;

                        GyR+=Gy[row][col]*pict.rgbtRed;
                        GyG+=Gy[row][col]*pict.rgbtGreen;
                        GyB+=Gy[row][col]*pict.rgbtBlue;
                    }
                }
            }
            int GRed=round(sqrt(GxR*GxR+GyR*GyR));
            int GGreen=round(sqrt(GxG*GxG+GyG*GyG));
            int GBlue=round(sqrt(GxB*GxB+GyB*GyB));

            if(GRed>255)
            {
            temp[i][j].rgbtRed=255;
            }
            else
            {
            temp[i][j].rgbtRed=GRed;
            }

            if(GGreen>255)
            {
            temp[i][j].rgbtGreen=255;
            }
            else
            {
            temp[i][j].rgbtGreen=GGreen;
            }

            if(GBlue>255)
            {
            temp[i][j].rgbtBlue=255;
            }
            else
            {
            temp[i][j].rgbtBlue=GBlue;
            }

           //temp[i][j].rgbtRed=GRed>255 ? 255: GRed;
           //temp[i][j].rgbtGreen=GGreen>255 ? 255: GGreen;
           //temp[i][j].rgbtBlue=GBlue>255 ? 255: GBlue;
        }
    }

    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width;j++)
        {
            image[i][j]= temp[i][j];
        }
    }
    return;
}
