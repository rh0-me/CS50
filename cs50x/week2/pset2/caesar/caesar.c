#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string encrypt(string input, int key);
bool validArg(string argv);
int main(int argc, string argv[])
{
    // command line validation
    if (argc != 2 || !validArg(argv[1]))
    {
        // Errorhandling
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // parse argv to int and between 0-26
    int key = atoi(argv[1]);
    key = key % 26;
    // Input
    string plaintext = get_string("plaintext:  ");

    // Output
    string ciphertext = encrypt(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
string encrypt(string input, int key)
{
    char resultChar[strlen(input) + 1];
    resultChar[strlen(input)] = '\0';
    // for input
    // resultChar = input[i]
    //  if alpha
    //  resultChar = input[i] + key
    // if islower
    // border = z, beginning = a
    // else = Z, beginning = a
    //  if resultchar > border
    //  shift = resultchar - border - 1, resultChar = beginning + shift
    // result[i] = resultChar
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        resultChar[i] = input[i];
        if (isalpha(resultChar[i]))
        {
            char beginning;
            char end;
            if (islower(input[i]))
            {
                beginning = 'a';
                end = 'z';
            }
            else
            {
                beginning = 'A';
                end = 'Z';
            }
            if ((int)input[i] + key > (int)end)
            {
                int shift = (int)input[i] + (int)key - (int)end - 1;
                resultChar[i] = beginning + shift;
            }
            else
            {
                resultChar[i] = input[i] + key;
            }
        }
    }
    string result = resultChar;
    return result;
}
bool validArg(string argv)
{
    // check if argv contains only digits
    // negative number or does not contain only digits
    bool isValidArg = true;
    for (int i = 0, lenArg = strlen(argv); i < lenArg; i++)
    {
        if (!isdigit(argv[i]))
        {
            isValidArg = false;
            return isValidArg;
        }
    }
    return isValidArg;
}