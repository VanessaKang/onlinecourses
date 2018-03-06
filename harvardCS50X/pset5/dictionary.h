/*
Name: Vanessa Kang
Course: Harvard Week 4
Challenge Name: speller
Purpose: This is the header file used to implement a program that spell-checks a file, using a given dictionary.
*/

// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define CHILDLENGTH 27

//Creating nodes for tries
typedef struct node{
    bool is_word;
    struct node *children[27];
}
node;

//Create the root pointer at the top of the try
node *rootpointer;

//Create a global variable to check if dictionary has been loaded
bool loadstate;

//Check for words in dictionary
int wordC;


// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

//Own created Prototypes
void unloading (node *unloader);
int sizecheck (node *sizeptr);


#endif // DICTIONARY_H

