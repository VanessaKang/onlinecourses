/*

Name: Vanessa Kang
Course: Harvard Week 2
Challenge Name: Crack (more)
Purpose: Design a program that can crack passwords, where each password has been hashed with C’s DES-based (not MD5-based) crypt function

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>
#define _XOPEN_SOURCE

/*Function Prototypes*/
int parameterCheck(int parameter);
int check(string crypted, string guess);
void removeSpace(char *array);
char *crypt(const char *key, const char *salt);

/*Makes sure only two arguments are passed by user or else it will keep asking with a usage example*/
int parameterCheck(int parameters)
{
    if (parameters != 2)
    {
        printf("Usage: ./crack hash\n");
        exit(1);
    }
    return 0;
}

/*Takes a character array to removes all spaces and returns a character array with no spaces*/
void removeSpace(char *array)
{
    // Count is used to count number of non-spaced characters
    int count = 0;
    //Takes characters without spaces and place it back into array
    for (int i = 0; array[i]; i++)
    {
        if (array[i] != ' ')
        {
            array[count++] = array[i];
        }
    }
    //Place '\0' at the end of the array to represent the end of a character array
    array[count] = '\0';
}

/*
    Checks if the array combination creates the same hash that the user passed into the program
    If the hashed password matches what the user wants us to decrpyt, then the original character
    array password will be printed out to the console
*/
int check(string crypted, string array)
{
    //removes spaces from character array
    removeSpace(array);
    /*Get the hash password of that character array using C’s DES-based (not MD5-based) crypt function
    which is the same function used for encrypting the password the user wants to crack*/
    string password = crypt(array,"50");
    /*Compare the hashed password with the password user wants us to decrypt
    If a match is made, the password from character array is output to console*/
    if (strcmp(password, crypted) == 0)
    {
        printf("%s\n", array);
        exit(0);
    }
    return 1;
}

/*
    Find password that can be up to 5 upper and lower characters that is encrypted using a hash function.
    The user will pass in the encrypted password for this program to crack
*/
int main(int argc, char *argv[])
{
    //Creates a character array for up to 5 different characters
    char array[5];
    //These are the possble combinations of characters that the password can used, including the space
    string letters = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //Checks if user has passed in the proper arguments when running this program
    parameterCheck(argc);
    //The second argument with the encrypted password is stored in crypted
    string crypted = argv[1];
    /*Goes through all the possible letter combinations in each index of the array
    and checks if it's respective hash matches the password that passes in. If a match is made
    then the cracked password is output to console*/
    for (int a = 0; a <strlen(letters);a++)
    {
        array[0] = letters[a];
        for (int b = 0; b < strlen(letters); b++)
        {
           array[1] = letters[b];
           for (int c = 0; c < strlen(letters); c++)
           {
               array[2] = letters[c];
               for (int d = 0; d < strlen(letters); d++)
               {
                   array[3] = letters[d];
                   for (int e =0; e < strlen(letters); e++)
                   {
                       array[4] = letters[e];
                       check(crypted, array);
                   }
               }
           }
       }
    }
}
