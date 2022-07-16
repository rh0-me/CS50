#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string encrypt(string plaintext, string key);
bool isValid(string arg);
int main(int argc, string argv[])
{
    // argc validation
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    // argv validation, key must ba 26 char long and should contain each letter A-Z caseinsensitive exactly once
    if (strlen(argv[1]) != 26 || !isValid(argv[1]))
    {
        printf("Key must contain 26 characters. Each letter exactly once");
        return 1;
    }
    // convert key to lower
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        argv[1][i] = tolower(argv[1][i]);
    }
    string key = argv[1];
    // input
    string plaintext = get_string("plaintext: ");
    string ciphertext = encrypt(plaintext, key);
    // output
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
bool isValid(string arg)
{
    // convert key to lowercase for checking
    for (int i = 0, len = strlen(arg); i < len; i++)
    {
        arg[i] = tolower(arg[i]);
    }

    // premise argLen = 26
    // check for alphabetical
    // check for multiple occurrences
    for (int i = 0, len = strlen(arg); i < len; i++)
    {
        if (isalpha(arg[i]) == 0)
        {
            return false;
        }
        for (int j = i + 1; j < len; j++)
        {
            if (arg[i] == arg[j])
            {
                return false;
            }
        }
    }
    return true;
}
// encrypts string, give a 26 char long key containing each letter once
string encrypt(string plaintext, string key)
{
    int len = strlen(plaintext);
    string ciphertext = plaintext;
    for (int i = 0; i < len; i++)
    {
        // check for alphabetical
        if (isalpha(plaintext[i]))
        {
            // check for uppercase
            if (isupper(plaintext[i]))
            {
                // map plainchar to keychar through position in key
                int position = (int)plaintext[i] - 65;
                ciphertext[i] = toupper(key[position]);
            }
            // lowercase
            else
            {
                int position = (int)plaintext[i] - 97;
                ciphertext[i] = tolower(key[position]);
            }
        }
    }
    return ciphertext;
}