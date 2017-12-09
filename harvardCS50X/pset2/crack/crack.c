#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>

#define _XOPEN_SOURCE


//Vanessa Kang
//Harvard Week 2
//Challenge Name: Crack (more)

//Purpose: Design a program that can crack passwords, where each password has been hashed with C’s DES-based (not MD5-based) crypt function.


int parameterCheck(int parameter);
int check(string crypted, string guess);
void removeSpace(char *array);
char *crypt(const char *key, const char *salt);

//Checks if there are only 2 parameters passed (including function call)
int parameterCheck(int parameters){
    if (parameters != 2){
        printf("Usage: ./crack hash\n");
        exit(1);
    }
    return 0;
}

//This function is there to remove spaces in a character array 
void removeSpace(char *array){
    // To keep track of non-space character count
    int count = 0;
 
    // If Character has no space, then put this character at index 'count' and increment 'count'
    for (int i = 0; array[i]; i++)
        if (array[i] != ' ')
            array[count++] = array[i]; 
                                   
    //As mentioned in cs50, '\0' should be at the end of a character array
    array[count] = '\0';
}

//Checks if the guessed password creates the same hash as input by the user
//If the password is cracked, the password will be printed onto the screen
int check(string crypted, string array){
    removeSpace(array);
    string password = crypt(array,"50");
    if (strcmp(password, crypted) == 0){
        printf("%s\n", array);
        exit(0);
    }
    return 1;
}


int main(int argc, char *argv[]){
    char array[5];
    
    //Passwords only included UpperCase and LowerCase letters
    //Space is included in the beginning to make sure there could be options for up to 4 letter combinations
    string letters = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    //Checks if parameter input is correct 
    parameterCheck(argc);
    
    //-------------------------------List of cracked codes to Test----------------
    //The hash code is a parameter passed by user
    string crypted = argv[1];
                
    
    //string crypted = "50i2t3sOSAZtk"; //lol
    //string crypted = "50fkUxYHbnXGw"; // ROFL
    //string crypted = "50.jPgLzVirkc"; //hi
    //string crypted = "50WUNAFdX/yjA"; //Yale
    
    
    //----------------------------------------------------------------------------
    
    // These loops goes through all the possible 4 letter (upper and lower) combination passwords
    //  Each loops goes through the letters array, looping through up to 4 character combinations
    for (int a = 0; a <strlen(letters);a++){
        array[0] = letters[a];
       for (int b = 0; b < strlen(letters); b++){
           array[1] = letters[b];
           for (int c = 0; c < strlen(letters); c++){
               array[2] = letters[c];
               for (int d = 0; d < strlen(letters); d++){
                   array[3] = letters[d];

                  //Check if guessed password creates a hash similar to what user passed through terminal
                  //Else, keeps checking different combinations with this loop
                   check(crypted, array);
               }
           }
       }
    }
}