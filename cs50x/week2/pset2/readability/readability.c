#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

void getGrade(string input);
int calcLetters(string input);
int calcWords(string input);
int calcSentences(string input);

int main(void)
{
    string input = get_string("Text: ");
    getGrade(input);
}
// Coleman-Liau index
void getGrade(string input)
{
    // calc letters, words and sentences
    int letters = calcLetters(input);
    int words = calcWords(input);
    int sentences = calcSentences(input);
    // average num of letters per 100 words
    double L = ((float)letters / (float)words) * 100;
    // average num of sentences per 100 words
    double S = ((float)sentences / (float)words) * 100;
    // Coleman-Liau Algorithm
    double index = index = 0.0588 * L - 0.296 * S - 15.8;
    // index rounded
    index = round(index);
    // output depending on index
    if (index >= 16)
    {
        index = 16;
        printf("Grade %i+\n", (int)index);
    }
    else if (index < 1)
    {
        index = 1;
        printf("Before Grade %i\n", (int)index);
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
}
// calc letters
int calcLetters(string input)
{
    int result = 0;
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        if (isalnum(input[i]))
        {
            result++;
        }
    }
    return result;
}
// calc words
int calcWords(string input)
{
    int result = 0;
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        if (isspace(input[i]))
        {
            result++;
        }
    }
    result++;
    return result;
}
// calc sentences
int calcSentences(string input)
{
    int result = 0;
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        if (input[i] == '!' || input[i] == '.' || input[i] == '?')
        {
            result++;
        }
    }
    return result;
}