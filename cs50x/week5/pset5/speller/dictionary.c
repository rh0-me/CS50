// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// my Prototypes
bool contains(node *root, const char *word);
void add(node *root, node *n);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// amount of words in the dictionary
int numberOfWords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return contains(table[hash(word)], word);
    bool result = false;
    node *linkedList = table[hash(word)];
    node *currentNode = linkedList;
    while (true)
    {
        if (currentNode == NULL)
        {
            break;
        }
        if (strcasecmp(word, currentNode->word) == 0)
        {
            result = true;
            break;
        }
        currentNode = currentNode->next;
    }
    return result;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hashValue = 0;
    hashValue = 26 * (toupper(word[0]) - 'A');
    if (isalpha(word[1]) != 0)
    {
        hashValue += (toupper(word[1]) - 'A');
    }
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char buffer[LENGTH + 1] = "";
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        unload();
        return false;
    }
    while (fscanf(dic, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        // add(table[1], n);
        n->next = table[hash(n->word)];
        table[hash(n->word)] = n;
        numberOfWords++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numberOfWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    bool result = false;
    for (int i = 0; i < N; i++)
    {
        node *currentNode;
        node *nextNode = table[i];
        while (true)
        {
            currentNode = nextNode;
            if (currentNode == NULL)
            {
                break;
            }
            nextNode = currentNode->next;
            free(currentNode);
        }
        if (i == N - 1)
        {
            result = true;
        }
    }
    return result;
}

// my functions
// add node to the end of a list
void add(node *root, node *n)
{
    if (root == NULL)
    {
        root = n;
        return;
    }
    else
    {
        add(root->next, n);
    }
}
// check if word is in linked list, traverse linked list nodes from root
bool contains(node *root, const char *word)
{
    if (strcasecmp(root->word, word) == 0)
    {
        return true;
    }
    else
    {
        if (root->next != NULL)
        {
            return contains(root->next, word);
        }
        else
        {
            return false;
        }
    }
}