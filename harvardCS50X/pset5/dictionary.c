/*
Name: Vanessa Kang
Course: Harvard Week 4
Challenge Name: speller
Purpose: Implement a program that spell-checks a file, using a given dictionary.

This implementation was done by creating a trie data structure of given dictionary words. Then spellchecking a text file.
Functions that were implemented were

    LOAD: Load dictionary into your choosing of data structure on the heap memory
    CHECK: Check a word from the file if it exists in the dictionary on memory
    UNLOAD: Remove dictionary trie off memory
    SIZE: Output the number of words in the dictionary

*/




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

    for (int j = 0; j < strlen(word) + 1; j++){

        //Check for bool = true to see if its a word
        if (word[j] =='\0' && level > 0){

            if (checkpointer->is_word == true){
                return true;
            }
            break;
        }

        //Gets index of an Aphostraphe
        if (word[j] == '\''){
            index = 26;
        }

        //Gets Index of alphabet letter whether its upper or lowercase
        else{
            if (isupper(word[j]) != 0){
                index = word[j] - 'A';
            }
            else{
                index = word[j] - 'a';
            }
        }

        //Checks if pointer to that index is NUll
        if (checkpointer->children[index] == NULL){
            break;
        }
        else {
            checkpointer = checkpointer->children[index];
            level += 1;
        }

    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char * dictionary)
{
    //Indicate that the file has not been loaded yet
    loadstate = false;

    //Counts number of words in dictionary
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
    while (fscanf(dictionaryfile, "%s", dictWord) != EOF)
    {
        //Word count
        wordC ++;

        //Create a for loop to go through all character variable
        for (int i = 0; i < sizeof(dictWord); i++)
        {

            //If its the end of the word, make sure to place is_word is true
            if (dictWord[i] == '\0' && level > 0)
            {

                adderpointer->is_word = true;
                break;
            }

            else
            {
                //Checks to see if its aphostraphe and get its index
                if (dictWord[i] == '\'')
                {
                    index = 26;
                }

                //Gets Index of alphabet letter
                else
                {
                    index = dictWord[i] - 'a';
                }


                if (adderpointer->children[index] == NULL)
                {

                    //Creating another node
                    node *addernode = NULL;
                    addernode = (node *)malloc(sizeof(node));

                    //Check if allocated memory is NULL
                    if (addernode == NULL)
                    {
                        fprintf(stderr, "Could not create adderpointer at level %i", level);
                        return 0;
                    }

                    //Create a node that has false and NULL values
                    addernode->is_word = false;
                    for (int child = 0; child < CHILDLENGTH; child ++)
                    {
                        addernode->children[child] = NULL;
                    }

                    //Add new NULL node to current child
                    adderpointer->children[index] = addernode;

                }
                //TRaverse to another node level
                adderpointer = adderpointer->children[index];
                level += 1;
            }
        }
        //Reset level and make pointer = root ot add another word
        level = 0;
        adderpointer = rootpointer;

        //Mkae dictWORD reset to NUL character
        memset(dictWord, '\0', sizeof(dictWord));
    }

    //Close dictionary file after all words have ran
    fclose(dictionaryfile);

    //Indicate that the dictionary has loaded onto memory
    loadstate = true;

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //If not loaded, return size of zero
    if (!loadstate){
        return 0;
    }

    //create new pointer to check for words in the trie
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

    //Indicate that the dictionary has been unloaded from memory
    loadstate = false;

    return true;
}


//Unloads children from memory
void unloading (node *unloader)
{
    //Iterate through each 27 children
    for (int i = 0; i < CHILDLENGTH; i++)
    {
        //If a Node exists, call the function again to free its children
        if (unloader->children[i])
        {
            unloading(unloader->children[i]);
        }

        //Else free that current pointer
        free(unloader->children[i]);
    }
}

int sizecheck (node *sizeptr)
{
    //initlize the sizecount to be zero
    int sizecount = 0;

    //Checks if at this particular pointer is the end of a word
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
