#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            float gemiddelde = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = round(gemiddelde);
            image[i][j].rgbtGreen = round(gemiddelde);
            image[i][j].rgbtRed = round(gemiddelde);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE geheugen[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            geheugen[i][width - j - 1] = image[i][j];
        }
    }
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = geheugen[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE geheugen[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            float gemiddeldeBlue = 0, gemiddeldeGreen = 0, gemiddeldeRed = 0;
            float somBlue = 0, somGreen = 0, somRed = 0;

            if (i > 0 && i < height - 1)
            {
                //Normal case
                if (j > 0 && j < width - 1)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int l = -1; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 9;
                    gemiddeldeRed = somRed / 9;
                    gemiddeldeGreen = somGreen / 9;
                }

                // uiterst rechtse pixels, niet de hoeken
                else if (j == width - 1)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int l = -1; l <= 0; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 6;
                    gemiddeldeRed = somRed / 6;
                    gemiddeldeGreen = somGreen / 6;
                }

                // Uiterst linkse pixels, niet de hoeken
                else if (j == 0)
                {
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int l = 0; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 6;
                    gemiddeldeRed = somRed / 6;
                    gemiddeldeGreen = somGreen / 6;
                }
            }
            else if (i == 0)
            {
                // bovenste rij pixels, niet de hoeken.
                if (j > 0 && j < width - 1)
                {
                    for (int k = 0; k <= 1; k++)
                    {
                        for (int l = -1; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 6;
                    gemiddeldeRed = somRed / 6;
                    gemiddeldeGreen = somGreen / 6;
                }

                // boven linkse hoek
                else if (j == 0)
                {
                    for (int k = 0; k <= 1; k++)
                    {
                        for (int l = 0; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 4;
                    gemiddeldeRed = somRed / 4;
                    gemiddeldeGreen = somGreen / 4;
                }

                // boven rechtse hoek
                else if (j == width - 1)
                {
                    for (int k = 0; k <= 1; k++)
                    {
                        for (int l = -1; l <= 0; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 4;
                    gemiddeldeRed = somRed / 4;
                    gemiddeldeGreen = somGreen / 4;
                }
            }
            else if (i == height - 1)
            {
                // Onderste rij pixels, niet de hoeken.
                if (j > 0 && j < width - 1)
                {
                    for (int k = -1; k <= 0; k++)
                    {
                        for (int l = -1; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 6;
                    gemiddeldeRed = somRed / 6;
                    gemiddeldeGreen = somGreen / 6;
                }

                // onder linkse hoek
                else if (j == 0)
                {
                    for (int k = -1; k <= 0; k++)
                    {
                        for (int l = 0; l <= 1; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 4;
                    gemiddeldeRed = somRed / 4;
                    gemiddeldeGreen = somGreen / 4;
                }

                // onder rechtse hoek
                else if (j == width - 1)
                {
                    for (int k = -1; k <= 0; k++)
                    {
                        for (int l = -1; l <= 0; l++)
                        {
                            somBlue = somBlue + (float) image[i + k][j + l].rgbtBlue;
                            somGreen = somGreen + (float) image[i + k][j + l].rgbtGreen;
                            somRed = somRed + (float) image[i + k][j + l].rgbtRed;
                        }
                    }
                    gemiddeldeBlue = somBlue / 4;
                    gemiddeldeRed = somRed / 4;
                    gemiddeldeGreen = somGreen / 4;
                }
            }


            geheugen[i][j].rgbtBlue = round(gemiddeldeBlue);
            geheugen[i][j].rgbtGreen = round(gemiddeldeGreen);
            geheugen[i][j].rgbtRed = round(gemiddeldeRed);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = geheugen[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE geheugen[height + 2][width + 2];

    //Voorzie geheugen[][] van zwarte randen.
    for (int i = 0; i < height + 2; i++)
    {
        geheugen[i][0].rgbtBlue = 0;
        geheugen[i][0].rgbtGreen = 0;
        geheugen[i][0].rgbtRed = 0;
        geheugen[i][width + 1].rgbtBlue = 0;
        geheugen[i][width + 1].rgbtGreen = 0;
        geheugen[i][width + 1].rgbtRed = 0;
    }
    for (int i = 0; i < width + 2; i++)
    {
        geheugen[0][i].rgbtBlue = 0;
        geheugen[0][i].rgbtGreen = 0;
        geheugen[0][i].rgbtRed = 0;
        geheugen[height + 1][i].rgbtBlue = 0;
        geheugen[height + 1][i].rgbtGreen = 0;
        geheugen[height + 1][i].rgbtRed = 0;
    }


    // Vul geheugeh[][] met de effectieve afbeelding.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            geheugen[i + 1][j + 1] = image[i][j];
        }
    }



    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int Gx;
            int Gy;

            Gx = geheugen[i - 1][j + 1].rgbtBlue + 2 * geheugen[i][j + 1].rgbtBlue + geheugen[i + 1][j + 1].rgbtBlue
                 - geheugen[i - 1][j - 1].rgbtBlue - 2 * geheugen[i][j - 1].rgbtBlue - geheugen[i + 1][j - 1].rgbtBlue;
            Gy = geheugen[i + 1][j - 1].rgbtBlue + 2 * geheugen[i + 1][j].rgbtBlue + geheugen[i + 1][j + 1].rgbtBlue
                 - geheugen[i - 1][j - 1].rgbtBlue - 2 * geheugen[i - 1][j].rgbtBlue - geheugen[i - 1][j + 1].rgbtBlue;
            
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
            }

            Gx = geheugen[i - 1][j + 1].rgbtRed + 2 * geheugen[i][j + 1].rgbtRed + geheugen[i + 1][j + 1].rgbtRed
                 - geheugen[i - 1][j - 1].rgbtRed - 2 * geheugen[i][j - 1].rgbtRed - geheugen[i + 1][j - 1].rgbtRed;
            Gy = geheugen[i + 1][j - 1].rgbtRed + 2 * geheugen[i + 1][j].rgbtRed + geheugen[i + 1][j + 1].rgbtRed
                 - geheugen[i - 1][j - 1].rgbtRed - 2 * geheugen[i - 1][j].rgbtRed - geheugen[i - 1][j + 1].rgbtRed;
            
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255)
            {
                image[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
            }
            
            Gx = geheugen[i - 1][j + 1].rgbtGreen + 2 * geheugen[i][j + 1].rgbtGreen + geheugen[i + 1][j + 1].rgbtGreen
                 - geheugen[i - 1][j - 1].rgbtGreen - 2 * geheugen[i][j - 1].rgbtGreen - geheugen[i + 1][j - 1].rgbtGreen;
            Gy = geheugen[i + 1][j - 1].rgbtGreen + 2 * geheugen[i + 1][j].rgbtGreen + geheugen[i + 1][j + 1].rgbtGreen
                 - geheugen[i - 1][j - 1].rgbtGreen - 2 * geheugen[i - 1][j].rgbtGreen - geheugen[i - 1][j + 1].rgbtGreen;
            
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255)
            {
                image[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
            }
        }
    }


    return;
}
