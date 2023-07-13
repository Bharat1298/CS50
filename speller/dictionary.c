// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
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
    int length = hash(word);
    int letter = hashLetter(word);

    bool check = false;

    node *arrow = table[length];

    while(arrow != NULL)
    {
        if(strcasecmp(word, arrow -> word) == 0){
            check = true;
            return true;
        }

        arrow = arrow -> next;

    }

    return check;
}

// Hashes word to a number
unsigned int hashLetter(const char *word)
{
    return sizeof(*word) / sizeof(word[0]) % N;
}

unsigned int hash(const char *word)
{
    return 0 ;//toupper(word[0]) - 'A';
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
        int letter = hashLetter(words -> word);

        words -> next = table[hashed];
        table[hashed] = words;

        wordCount++;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
