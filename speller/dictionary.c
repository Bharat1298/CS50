// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = LENGTH;

// Hash table
node *table[N];

// Word Count
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash =
    }
    return sizeof(*word) / sizeof(word[0]) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");

    if(input == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while(fscanf(input, "%s", word) != EOF)
    {
        node *words = malloc(sizeof(node));

        if(words == NULL)
        {
            return false;
        }

        strcpy(words -> word, word);

        int hashed = hash(words -> word);

        words -> next = NULL;

        if(table[hashed] == NULL)
        {
            table[hashed] = words;
        }
        else
        {
            words -> next = table[hashed];
            table[hashed] = words;
        }

        wordCount++;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(load)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
