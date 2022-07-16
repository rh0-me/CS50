#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // check for arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    // open raw file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int imgCounter = -1;
    char filename[8];
    filename[7] = '\0';
    FILE *img;
    // read raw file in 512 Bytes chunks
    while (fread(buffer, 1, BLOCK_SIZE, file))
    {
        // checks for jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // increase counter to point to current img
            imgCounter++;
            // if it's not the first image, close the one before
            if (imgCounter != 0)
            {
                fclose(img);
            }
            // create filename, depending on current img
            sprintf(filename, "%03i.jpg", imgCounter);
            img = fopen(filename, "w");
            if (!img)
            {
                return 2;
                printf("Imagefile can not be created");
            }
        }
        // if there is a jpg, write to img file
        if (imgCounter >= 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }
    // checks if filepointer is valid
    if (img == NULL)
    {
        printf("Imgfile does not exist");
        return 3;
    }
    fclose(img);
    // close raw file
    fclose(file);
}