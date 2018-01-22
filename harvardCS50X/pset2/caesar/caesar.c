/*
    Name: Vanessa Kang
    Course: Harvard CS50x
    Problem: Caesar
    Purpose: Implement a program that encrypts messages using Caesar’s cipher.

    ---------Example-------
        $ ./caesar 13
        plaintext:  HELLO
        ciphertext: URYYB
    -----------------------
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*Program Prototypes*/
void argumentCheck(int argc);
int keyCheck(char *argv[]);
void plainTextCheck(string plainText);
void caesarsCharacters(string plainText, int key);

/*Analyze number of arguments and will terminate if there is not two*/
void argumentCheck(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        exit(1);
    }
}

/*Takes in the second argument (the key) to check if its an integer and returns the integer*/
int keyCheck(char *argv[])
{
    //Convert String Integer --> Integer
    string stringKey = argv[1];
    int key = atoi(stringKey);

    //Program terminates if not an integer
    if (key == 0)
    {
        printf("Not a number\n");
        exit(1);
    }
    return key;
}

/*If the user wrote nothing, it will terminate the program*/
void plainTextCheck(string plainText)
{
    if ((plainText == NULL) || (strcmp(plainText, "") == 0))
    {
        printf("Please enter something.\n");
        exit(1);
    }
}

/*Encrypts messages with Caesar’s cipher using a key to shift the letters in the alphabet.*/
void caesarsCharacters(string plainText, int key)
{
    //Analyzes each character from plaintext and shifts the ascii number by the "key" and then print out
    //the corresponding character. This is done to all characters in the plaintext.
    //Resulting caesar character is printed out.
        for (int i= 0; plainText[i]; i++)
    {
        if (isalpha(plainText[i]))
        {
            if (islower(plainText[i])){
                int alphaNum = plainText[i] - 97;
                int keyAlphaNum = (alphaNum + key) % 26;
                char cipherChar = keyAlphaNum + 97;
                printf("%c",cipherChar);

            }
            if (isupper(plainText[i])){
                int alphaNum = plainText[i] - 65;
                int keyAlphaNum = (alphaNum + key) % 26;
                char cipherChar = keyAlphaNum + 65;
                printf("%c",cipherChar);
            }
        }
        else
        {   //if there are spaces or other sympbols, make sure to not shift it
            printf("%c", plainText[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    //Program will exit if there is not 2 arguments passed
    argumentCheck(argc);

    //Takes the key and converts it to integer if its an integer string
    int key = keyCheck(argv);

    //Gets Input from user of plaintext they want to encrypt with caesear's encryption
    string plainText = get_string("plaintext:  ");

    //Check if user wrote something valid
    plainTextCheck(plainText);
    printf("ciphertext: ");

    //Encrypts messages using Caesar’s cipher with a given key and prints out the characters
    caesarsCharacters(plainText, key);
    printf("\n");
}
