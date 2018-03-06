// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#include "unused.h"

// Returns true if word is in dictionary else false
bool check(const char * word)
{
    //Creates a pointer at the root
    node *checkpointer = rootpointer;
    int level = 0;
    int index;

    //printf("---NEW WORD---\n");

    for (int j = 0; j < strlen(word) + 1; j++){

        //Check for bool = true to see if its a word
        if (word[j] =='\0' && level > 0){
            //printf ("Checking if True\n");
            if (checkpointer->is_word == true){
                //printf("WOOT ITS THERE\n");
                return true;
            }
            break;
        }

        //Gets index of an Aphostraphe
        if (word[j] == '\''){
            index = 26;
            //printf ("Aphospraphe with Index: %d --%c  :\n", index, word[j]);
        }

        //Gets Index of alphabet letter whether its upper or lowercase
        else{
            if (isupper(word[j]) != 0){
                index = word[j] - 'A';
            }
            else{
                index = word[j] - 'a';
            }
            //printf ("Letter with Index: %d --%c  :\n", index, word[j]);
        }

        //Checks if pointer to that index is NUll
        if (checkpointer->children[index] == NULL){
            //printf("Found a NULL pointer for character %c\n", word[j]);
            break;
        }
        else {
            checkpointer = checkpointer->children[index];
            level += 1;
            //printf("Moving onto Level %i \n", level);
        }

    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char * dictionary)
{
    loadstate = false;
    wordC = 0;
    //Malloc address for rootpointer for the size of node
    node *rootnode = NULL;
    rootnode = (node *)malloc(sizeof(node));

    //Checks if malloc has room
    if (rootnode == NULL)
    {
        fprintf(stderr, "Could not create rootpointer");
        return 0;
    }

    //Initlize is_word as false
    rootnode->is_word = false;
    //printf("What is Is_word: %i\n",rootpointer->is_word);

    //Initialize root children[] array as NULL
    for (int child = 0; child < CHILDLENGTH; child ++)
    {
        rootnode->children[child] = NULL;
    }
    rootpointer = rootnode;

    //Create a char array to hold each word read from dictionary
    char dictWord[LENGTH+1] ={'\0'};

    //Open a file
    FILE* dictionaryfile = fopen(dictionary, "r");

    //Checks if there is any error opening files
    if (dictionaryfile == NULL)
    {
        fprintf(stderr, "Could not open %s. in load function\n", dictionary);
        return 0;
    }

    //Create index varable depending on letter
    int index;
    int level = 0;

    //Create an alternative pointer
    node *adderpointer = rootpointer;

    //Read a word from file
    //if End of File, all words has been read from dictionary
    while (fscanf(dictionaryfile, "%s", dictWord) != EOF)
    {
        wordC ++;
        //Create a for loop to go through all character variable
        for (int i = 0; i < sizeof(dictWord); i++)
        {

            //If its the end of the word, make sure to place is_word is true
            if (dictWord[i] == '\0' && level > 0)
            {
                //printf("---------------This is the end (Making is_word = true)---------------\n");
                adderpointer->is_word = true;
                break;
            }

            else
            {
                //Checks to see if its aphostraphe and get its index
                if (dictWord[i] == '\'')
                {
                    index = 26;
                    //printf ("Aphospraphe with Index: %d --%c  :\n", index, dictWord[i]);
                }

                //Gets Index of alphabet letter
                else
                {
                    index = dictWord[i] - 'a';
                    //printf("Letter with Index: %d --%c   :\n", index, dictWord[i]);
                }


                if (adderpointer->children[index] == NULL)
                {
                    //printf("NULL : so creating another level \n");

                    //Creating another node
                    node *addernode = NULL;
                    addernode = (node *)malloc(sizeof(node));

                    if (addernode == NULL)
                    {
                        fprintf(stderr, "Could not create adderpointer at level %i", level);
                        return 0;
                    }

                    addernode->is_word = false;
                    for (int child = 0; child < CHILDLENGTH; child ++)
                    {
                        addernode->children[child] = NULL;
                    }

                    adderpointer->children[index] = addernode;

                }
                adderpointer = adderpointer->children[index];
                level += 1;
            }
        }
        //printf("-------The Level is %i-----------\n", level);
        level = 0;
        adderpointer = rootpointer;
        memset(dictWord, '\0', sizeof(dictWord));
    }

    fclose(dictionaryfile);
    loadstate = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!loadstate){
        return 0;
    }

    node *sizepointer = rootpointer;

    return sizecheck(sizepointer);
    //return wordC;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Get the root pointer for rootpointer
    node *unloadptr = rootpointer;

    //Pass Root pointer to unloading function to free children
    unloading(unloadptr);

    //After finishing freeing children, free the root pointer
    free(unloadptr);

    loadstate = false;
    return true;
}


//Unloads children from memory
void unloading (node *unloader)
{
    //Iterate through each 27 child
    for (int i = 0; i < CHILDLENGTH; i++)
    {
        //If a Node exists, call the function again to free its children
        if (unloader->children[i])
        {
            unloading(unloader->children[i]);
        }

        //Else Free that pointer
        free(unloader->children[i]);
    }
}

int sizecheck (node *sizeptr)
{
    //initlize the size to be zero everytime
    int sizecount = 0;

    //Checks if at this particular pointer has a true
    if (sizeptr->is_word == true)
    {
        sizecount +=1;
    }

    //Check all children in node
    for (int i = 0; i < CHILDLENGTH; i++)
    {
        if (sizeptr->children[i])
        {
            sizecount += sizecheck(sizeptr->children[i]);
        }
    }

    return sizecount;
}
