// Implements a dictionary's functionality

#include <ctype.h>
#include <strings.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//assign the value
unsigned int count_of_word;
unsigned int value_of_hash;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // check if the word exist in dictionary
    value_of_hash = hash(word);
    //look to the first node
    node *cursor = table[value_of_hash];
    //iterate through the list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        //if not move it to the next node
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    //return null if cannot open
    if (file == NULL)
    {
        printf("unable to open file %s\n", dictionary);
        return false;
    }
    //stroring word
    char word[LENGTH + 1];
    //look for string until end
    while (fscanf(file, "%s", word) != EOF)
    {
        //memory allocation for new meory
        node *n = malloc(sizeof(node));
        //if its none send back false
        if (n == NULL)
        {
            return false;
        }
        //now get the word to the node
        strcpy(n->word, word);
        value_of_hash = hash(word);
        n->next = table[value_of_hash];
        table[value_of_hash] = n;
        count_of_word++;

    }
    //closing the file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //find out what the size of the dictionary and return
    if (count_of_word > 0)
    {
        return count_of_word;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // go through load
    for (int i = 0; i < N; i++)
    {
        //cursor now has to be equal to the list
        node *cursor = table[i];
        //however if it is NULL we have to free the memory use
        while (cursor != NULL)
        {
            node *temp = cursor;
            //go to the next node
            cursor = cursor->next;
            //natural you then free the memory just use
            free(temp);
        }
        //this is to check if we have reach the end of the list
    }

    return true;
}
