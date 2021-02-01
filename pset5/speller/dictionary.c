
// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>
#include <math.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hou het aantal woorden bij, voor word_count()
unsigned int aantalWoorden = 0;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(char *word)
{
    int hash_index = hash(word);

    node *n = table[hash_index];
    if (n == NULL)
    {
        return false;
    }

    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(char *word)
{

    int hash_index = (int)toupper(word[0]) - (int)'A' - 1;
    return hash_index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open de dictionary
    int hash_index;
    FILE *dict = fopen(dictionary, "r");

    // Als de dictionary niet tegoei geopend is, return false
    if (dict == NULL)
    {
        return false;
    }

    // Creër ruimte om het ingelezen woord in op te slaan.
    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {
        //Tel het aantal woorden
        aantalWoorden++;

        // creër geheugen voor nieuwe node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // Creër een node voor het nieuwe ingelezen woord.
        // Sla ze op in hoofdletters, behandel ALLES in hoofdletters.
        strcpy(n->word, word);
        // Lees de hashindex in voor dit woord.
        hash_index = hash(word);
        // zet een pointer van de vorige node in de hashtable naar de huidige node
        n->next = table[hash_index];
        //  Plaats node n ook in de hash table.
        table[hash_index] = n;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return aantalWoorden;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *n;
    for (int i = 0; i < N; i++)
    {
        n = table[i];

        while (n != NULL)
        {
            node *t = n;
            n = n -> next;
            free(t);
        }
    }
    return true;
}
