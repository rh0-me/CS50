#include <cs50.h>
#include <stdio.h>

int main(void)
{
    bool validInput = false;
    int height;
    // Inputvalidation
    while (!validInput)
    {
        height = get_int("Height: ");
        if (1 <= height && height <= 8)
        {
            validInput = true;
        }
    }

    for (int i = 1; i <= height; i++)
    {
        // Right-aligned pyramid
        // Print Spaces
        int spaces = height - i;
        while (spaces != 0)
        {
            printf(" ");
            spaces--;
        }
        // Print #
        int hashesLeft = i;
        while (hashesLeft != 0)
        {
            printf("#");
            hashesLeft--;
        }
        // Gap
        printf("  ");
        // Left-aligned pyramdid
        // Print #
        int hashesRight = i;
        while (hashesRight != 0)
        {
            printf("#");
            hashesRight--;
        }
        printf("\n");
    }
}