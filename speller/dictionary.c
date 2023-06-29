// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 52;

FILE *fh;
int words_number;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node* temp = table[index];

    while (temp!=NULL)
    {
        if (strcasecmp(word, temp->word)==0)
        {
            return true;
        }
        temp=temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int h=toupper(word[0]) -'A';
    int l=strlen(word);
    if(l%2==0) //chet kolvo
    {
        if (h%2==0)//chet index
        {
            return h;
        }
        else  //nechet index
        {
            return h+1;
        }
    }
    else //ne chet kolvo
    {
        if (h%2==0)//chet index
        {
            return h+1;
        }
        else //ne chet index
        {
            return h;
        }
    }


    //return (toupper(s[0]) -'A') % max_size;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    fh=fopen(dictionary, "r");
    if (fh==NULL)
    {
        printf ("Error");
        return false;
    }
    char word_temp[LENGTH+1];
    while (fscanf(fh,"%s",word_temp)!=EOF)
    {
        node *temp=malloc(sizeof(node));
        if (temp==NULL)
        {
            return false;
        }
        strcpy(temp->word, word_temp);
        int index = hash(word_temp);
        temp->next=table[index];
        table[index]=temp;
        words_number++;
    }
    fclose(fh);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_number;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i=0;i<N;i++)
    {
        node *temp=table[i];
        node *prev=table[i];

        while (temp!=NULL)
        {
            temp = temp->next;
            free(prev);
            prev = temp;
        }
    }
    return true;
}