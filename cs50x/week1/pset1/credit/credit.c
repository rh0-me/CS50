#include <cs50.h>
#include <stdio.h>

int getLength(long number);
void getDigits(long number, int digits[]);
void identifyCard(int digitCount, int digits[]);
bool checkSum(long number, int digitCount);

int main(void)
{
    // Input Number
    long number = get_long("Number: ");
    // Number > 0, else Number is invalid
    if (number > 0)
    {
        // Get digitcount
        int digitCount = getLength(number);
        int digits[digitCount];
        // Get digits
        getDigits(number, digits);
        // Identification Credit Card
        if (checkSum(number, digitCount))
        {
            identifyCard(digitCount, digits);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
// Return the count of digits from a given number
int getLength(long number)
{
    int count = 0;
    while (number != 0)
    {
        number = number / 10;
        count++;
    }
    return count;
}
// Returns the pointer to the beginning of the array, cointaining digits of the given number
void getDigits(long number, int digits[])
{
    int i = 0;
    while (number != 0)
    {
        digits[i] = number % 10;
        number = number / 10;
        i++;
    }
}
//
void identifyCard(int digitCount, int digits[])
{
    // Amex
    if (digitCount == 15 && digits[digitCount - 1] == 3 && (digits[digitCount - 2] == 4 || digits[digitCount - 2] == 7))
    {
        printf("AMEX\n");
    }
    // VISA with 13 digits
    else if (digitCount == 13 && digits[digitCount - 1] == 4)
    {
        printf("VISA\n");
    }
    else if (digitCount == 16)
    {
        // VISA with 16 digits and constraints
        if (digits[digitCount - 1] == 4)
        {
            printf("VISA\n");
        }
        // MasterCard 16 digits
        else if (digits[digitCount - 1] == 5)
        {
            if (digits[digitCount - 2] == 1 || digits[digitCount - 2] == 2 || digits[digitCount - 3] == 1 || digits[digitCount - 2] == 4
                || digits[digitCount - 2] == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
bool checkSum(long number, int digitCount)
{
    bool result = false;
    // Array with saved digits
    int d[digitCount];
    int i = 0;
    while (number != 0)
    {
        d[i] = number % 10;
        number = number / 10;
        i++;
    }
    int sumP = 0;
    int sumS = 0;
    for (int k = 0 ; k < digitCount; k++)
    {
        // Double every 2nd digit and sum product digits
        if (k % 2 == 1)
        {
            int temp = d[k] * 2;
            while (temp != 0)
            {
                sumP += temp % 10;
                temp = temp / 10;
            }
        }
        else
        {
            sumS += d[k];
        }
    }
    int total = sumP + sumS;
    if (total % 10 == 0)
    {
        result = true;
    }
    return result;
}