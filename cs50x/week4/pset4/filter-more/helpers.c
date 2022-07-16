#include "helpers.h"
#include <math.h>

double calcGxRed(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double calcGxGreen(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double calcGxBlue(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double calcGyRed(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double calcGyGreen(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double calcGyBlue(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
void limitColor(int *color);

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
                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                           6.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                              copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                             6.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                            6.0;
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
                            copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                           6.0;
                    aGreen = (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                              copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                             6.0;
                    aBlue = (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                             copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                            6.0;
                }
            }
            // left edge
            else if (j == 0 && (i != 0 || i != height - 1))
            {
                aRed = (copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                        copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                       6.0;
                aGreen = (copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                          copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                         6.0;
                aBlue = (copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                         copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                        6.0;
            }
            // right edge
            else if (j == width - 1 && (i != 0 || i != height - 1))
            {
                aRed = (copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                        copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                       6.0;
                aGreen = (copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                          copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                         6.0;
                aBlue = (copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                         copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                        6.0;
            }
            // middle
            else
            {
                aRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                        copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                        copy[i + 1][j + 1].rgbtRed) /
                       9.0;
                aGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                          copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                          copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                         9.0;
                aBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                         copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                         copy[i + 1][j + 1].rgbtBlue) /
                        9.0;
            }
            image[i][j].rgbtRed = (int)round(aRed);
            image[i][j].rgbtGreen = (int)round(aGreen);
            image[i][j].rgbtBlue = (int)round(aBlue);
        }
    }

    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    double GxRed = 0;
    double GxGreen = 0;
    double GxBlue = 0;
    double GyRed = 0;
    double GyGreen = 0;
    double GyBlue = 0;
    int tmpRed, tmpGreen, tmpBlue;
    // copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // calc edges
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxRed = calcGxRed(i, j, height, width, copy);
            GxGreen = calcGxGreen(i, j, height, width, copy);
            GxBlue = calcGxBlue(i, j, height, width, copy);
            GyRed = calcGyRed(i, j, height, width, copy);
            GyGreen = calcGyGreen(i, j, height, width, copy);
            GyBlue = calcGyBlue(i, j, height, width, copy);

            tmpRed = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            tmpGreen = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            tmpBlue = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            limitColor(&tmpRed);
            limitColor(&tmpGreen);
            limitColor(&tmpBlue);
            image[i][j].rgbtRed = tmpRed;
            image[i][j].rgbtGreen = tmpGreen;
            image[i][j].rgbtBlue = tmpBlue;
        }
    }
    return;
}
void limitColor(int *color)
{
    if (*color > 255)
    {
        *color = 255;
    }
}
// calc Gx for red
double calcGxRed(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtRed;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtRed;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtRed;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtRed;
            midMid = copy[i][j].rgbtRed;
            midRight = copy[i][j + 1].rgbtRed;
            botLeft = copy[i + 1][j - 1].rgbtRed;
            botMid = copy[i + 1][j].rgbtRed;
            botRight = copy[i + 1][j + 1].rgbtRed;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtRed;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtRed;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtRed;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtRed;
            topRight = copy[i - 1][j + 1].rgbtRed;
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = copy[i][j + 1].rgbtRed;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = copy[i - 1][j + 1].rgbtRed;
        midLeft = 0;
        midMid = copy[i][j].rgbtRed;
        midRight = copy[i][j + 1].rgbtRed;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = copy[i + 1][j + 1].rgbtRed;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtRed;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtRed;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = copy[i - 1][j + 1].rgbtRed;
        midLeft = copy[i][j - 1].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        midRight = copy[i][j + 1].rgbtRed;
        botLeft = copy[i + 1][j - 1].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = copy[i + 1][j + 1].rgbtRed;
    }

    return (double)(-topLeft - 2 * midLeft - botLeft + topRight + 2 * midRight + botRight);
}
// calc Gx for a green
double calcGxGreen(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtGreen;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtGreen;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtGreen;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtGreen;
            midMid = copy[i][j].rgbtGreen;
            midRight = copy[i][j + 1].rgbtGreen;
            botLeft = copy[i + 1][j - 1].rgbtGreen;
            botMid = copy[i + 1][j].rgbtGreen;
            botRight = copy[i + 1][j + 1].rgbtGreen;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtGreen;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtGreen;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtGreen;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtGreen;
            topRight = copy[i - 1][j + 1].rgbtGreen;
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = copy[i][j + 1].rgbtGreen;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = copy[i - 1][j + 1].rgbtGreen;
        midLeft = 0;
        midMid = copy[i][j].rgbtGreen;
        midRight = copy[i][j + 1].rgbtGreen;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = copy[i + 1][j + 1].rgbtGreen;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtGreen;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtGreen;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = copy[i - 1][j + 1].rgbtGreen;
        midLeft = copy[i][j - 1].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        midRight = copy[i][j + 1].rgbtGreen;
        botLeft = copy[i + 1][j - 1].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = copy[i + 1][j + 1].rgbtGreen;
    }

    return (double)(-topLeft - 2 * midLeft - botLeft + topRight + 2 * midRight + botRight);
}
// calc Gx for blue
double calcGxBlue(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtBlue;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtBlue;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtBlue;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtBlue;
            midMid = copy[i][j].rgbtBlue;
            midRight = copy[i][j + 1].rgbtBlue;
            botLeft = copy[i + 1][j - 1].rgbtBlue;
            botMid = copy[i + 1][j].rgbtBlue;
            botRight = copy[i + 1][j + 1].rgbtBlue;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtBlue;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtBlue;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtBlue;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtBlue;
            topRight = copy[i - 1][j + 1].rgbtBlue;
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = copy[i][j + 1].rgbtBlue;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = copy[i - 1][j + 1].rgbtBlue;
        midLeft = 0;
        midMid = copy[i][j].rgbtBlue;
        midRight = copy[i][j + 1].rgbtBlue;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = copy[i + 1][j + 1].rgbtBlue;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtBlue;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtBlue;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = copy[i - 1][j + 1].rgbtBlue;
        midLeft = copy[i][j - 1].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        midRight = copy[i][j + 1].rgbtBlue;
        botLeft = copy[i + 1][j - 1].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = copy[i + 1][j + 1].rgbtBlue;
    }

    return (double)(-topLeft - 2 * midLeft - botLeft + topRight + 2 * midRight + botRight);
}
// calc Gy for red
double calcGyRed(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtRed;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtRed;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtRed;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtRed;
            midMid = copy[i][j].rgbtRed;
            midRight = copy[i][j + 1].rgbtRed;
            botLeft = copy[i + 1][j - 1].rgbtRed;
            botMid = copy[i + 1][j].rgbtRed;
            botRight = copy[i + 1][j + 1].rgbtRed;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtRed;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtRed;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtRed;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtRed;
            topRight = copy[i - 1][j + 1].rgbtRed;
            midLeft = copy[i][j - 1].rgbtRed;
            midRight = copy[i][j + 1].rgbtRed;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = copy[i - 1][j + 1].rgbtRed;
        midLeft = 0;
        midMid = copy[i][j].rgbtRed;
        midRight = copy[i][j + 1].rgbtRed;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = copy[i + 1][j + 1].rgbtRed;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtRed;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtRed;
        topMid = copy[i - 1][j].rgbtRed;
        topRight = copy[i - 1][j + 1].rgbtRed;
        midLeft = copy[i][j - 1].rgbtRed;
        midMid = copy[i][j].rgbtRed;
        midRight = copy[i][j + 1].rgbtRed;
        botLeft = copy[i + 1][j - 1].rgbtRed;
        botMid = copy[i + 1][j].rgbtRed;
        botRight = copy[i + 1][j + 1].rgbtRed;
    }

    return (double)(-topLeft - 2 * topMid - topRight + botLeft + 2 * botMid + botRight);
}
// calc Gy for green
double calcGyGreen(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtGreen;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtGreen;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtGreen;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtGreen;
            midMid = copy[i][j].rgbtGreen;
            midRight = copy[i][j + 1].rgbtGreen;
            botLeft = copy[i + 1][j - 1].rgbtGreen;
            botMid = copy[i + 1][j].rgbtGreen;
            botRight = copy[i + 1][j + 1].rgbtGreen;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtGreen;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtGreen;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtGreen;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtGreen;
            topRight = copy[i - 1][j + 1].rgbtGreen;
            midLeft = copy[i][j - 1].rgbtGreen;
            midRight = copy[i][j + 1].rgbtGreen;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = copy[i - 1][j + 1].rgbtGreen;
        midLeft = 0;
        midMid = copy[i][j].rgbtGreen;
        midRight = copy[i][j + 1].rgbtGreen;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = copy[i + 1][j + 1].rgbtGreen;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtGreen;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtGreen;
        topMid = copy[i - 1][j].rgbtGreen;
        topRight = copy[i - 1][j + 1].rgbtGreen;
        midLeft = copy[i][j - 1].rgbtGreen;
        midMid = copy[i][j].rgbtGreen;
        midRight = copy[i][j + 1].rgbtGreen;
        botLeft = copy[i + 1][j - 1].rgbtGreen;
        botMid = copy[i + 1][j].rgbtGreen;
        botRight = copy[i + 1][j + 1].rgbtGreen;
    }

    return (double)(-topLeft - 2 * topMid - topRight + botLeft + 2 * botMid + botRight);
}
// calc Gy for blue
double calcGyBlue(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int topLeft;
    int topMid;
    int topRight;
    int midLeft;
    int midMid;
    int midRight;
    int botLeft;
    int botMid;
    int botRight;

    // edge handling
    if (i == 0)
    {
        topLeft = 0;
        topMid = 0;
        topRight = 0;
        midMid = copy[i][j].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        // top left corner
        if (j == 0)
        {
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtBlue;
            botLeft = 0;
            botRight = copy[i + 1][j + 1].rgbtBlue;
        }
        // top right corner
        else if (j == width - 1)
        {
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = 0;
            botLeft = copy[i + 1][j - 1].rgbtBlue;
            botRight = 0;
        }
        // top edge
        else
        {
            midLeft = copy[i][j - 1].rgbtBlue;
            midMid = copy[i][j].rgbtBlue;
            midRight = copy[i][j + 1].rgbtBlue;
            botLeft = copy[i + 1][j - 1].rgbtBlue;
            botMid = copy[i + 1][j].rgbtBlue;
            botRight = copy[i + 1][j + 1].rgbtBlue;
        }
    }
    else if (i == height - 1)
    {
        topMid = copy[i - 1][j].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        botLeft = 0;
        botMid = 0;
        botRight = 0;
        // bot left corner
        if (j == 0)
        {
            topLeft = 0;
            topRight = copy[i - 1][j + 1].rgbtBlue;
            midLeft = 0;
            midRight = copy[i][j + 1].rgbtBlue;
        }
        // bot right corner
        else if (j == width - 1)
        {
            topLeft = copy[i - 1][j - 1].rgbtBlue;
            topRight = 0;
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = 0;
        }
        // bot edge
        else
        {
            topLeft = copy[i - 1][j - 1].rgbtBlue;
            topRight = copy[i - 1][j + 1].rgbtBlue;
            midLeft = copy[i][j - 1].rgbtBlue;
            midRight = copy[i][j + 1].rgbtBlue;
        }
    }
    else if (j == 0)
    {
        // left edge
        topLeft = 0;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = copy[i - 1][j + 1].rgbtBlue;
        midLeft = 0;
        midMid = copy[i][j].rgbtBlue;
        midRight = copy[i][j + 1].rgbtBlue;
        botLeft = 0;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = copy[i + 1][j + 1].rgbtBlue;
    }
    else if (j == width - 1)
    {
        // right edge
        topLeft = copy[i - 1][j - 1].rgbtBlue;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = 0;
        midLeft = copy[i][j - 1].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        midRight = 0;
        botLeft = copy[i + 1][j - 1].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = 0;
    }

    // default case: middle pixels
    else
    {
        topLeft = copy[i - 1][j - 1].rgbtBlue;
        topMid = copy[i - 1][j].rgbtBlue;
        topRight = copy[i - 1][j + 1].rgbtBlue;
        midLeft = copy[i][j - 1].rgbtBlue;
        midMid = copy[i][j].rgbtBlue;
        midRight = copy[i][j + 1].rgbtBlue;
        botLeft = copy[i + 1][j - 1].rgbtBlue;
        botMid = copy[i + 1][j].rgbtBlue;
        botRight = copy[i + 1][j + 1].rgbtBlue;
    }

    return (double)(-topLeft - 2 * topMid - topRight + botLeft + 2 * botMid + botRight);
}