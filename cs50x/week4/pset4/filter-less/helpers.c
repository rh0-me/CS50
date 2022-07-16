#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float result = 0;
    // average pixelvalue across rgb
    // for every row
    for (int i = 0; i < height; i++)
    {
        // for every pixel in a row
        for (int j = 0; j < width; j++)
        {
            // result = average of rgb
            result = (float)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtBlue = (int)round(result);
            image[i][j].rgbtRed = (int)round(result);
            image[i][j].rgbtGreen = (int)round(result);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    // sepia algorithmn, cap at 255
    // for every row
    for (int i = 0; i < height; i++)
    {
        // for every pixel in a row
        for (int j = 0; j < width; j++)
        {
            // calc sepiavalue for rgb
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            // cap sepiavalue at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // assign sepia rgb to pixel
            image[i][j].rgbtRed = (int)round(sepiaRed);
            image[i][j].rgbtGreen = (int)round(sepiaGreen);
            image[i][j].rgbtBlue = (int)round(sepiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    // swap pixels in a row
    // for every row
    for (int i = 0; i < height; i++)
    {
        // for every pixel in a row
        for (int j = 0; j < width / 2; j++)
        {
            // swap pixels in row
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of original image, for calculation of blurred image with "box blur"
    RGBTRIPLE copy[height][width];
    float aGreen;
    float aRed;
    float aBlue;
    // copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // calculate blurpixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                // top left corner
                if (j == 0)
                {
                    aRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0;
                    aGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0;
                    aBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0;
                }
                // top right corner
                else if (j == width - 1)
                {
                    aRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0;
                }
                // top edge
                else
                {
                    aRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                              copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0;
                }
            }
            else if (i == height - 1)
            {
                // bottom left corner
                if (j == 0)
                {
                    aRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4.0;
                    aGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4.0;
                    aBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4.0;
                }
                // bottom right corner
                else if (j == width - 1)
                {
                    aRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) / 4.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / 4.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / 4.0;
                }
                // bottom edge
                else
                {
                    aRed = (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                            copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                              copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                             copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0;
                }
            }
            // left edge
            else if (j == 0 && (i != 0 || i != height - 1))
            {
                aRed = (copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                        copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0;
                aGreen = (copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                          copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0;
                aBlue = (copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                         copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0;
            }
            // right edge
            else if (j == width - 1 && (i != 0 || i != height - 1))
            {
                aRed = (copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                        copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0;
                aGreen = (copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                          copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0;
                aBlue = (copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                         copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0;
            }
            // middle
            else
            {
                aRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                        copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                        copy[i + 1][j + 1].rgbtRed) / 9.0;
                aGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                          copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                          copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0;
                aBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                         copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                         copy[i + 1][j + 1].rgbtBlue) / 9.0;
            }
            image[i][j].rgbtRed = (int)round(aRed);
            image[i][j].rgbtGreen = (int)round(aGreen);
            image[i][j].rgbtBlue = (int)round(aBlue);
        }
    }

    return;
}
