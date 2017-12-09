#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Vanessa Kang
//Harvard Week 2
//Challenge Name: Initials (More)
//Purpose: Implement a program that, given a person’s name, prints a person’s initials

int main(void){
    char letter; 
    char next;
    char first;
    
    //Obtain Name from User
    string name = get_string();

    //Check if first character of string is a name
    first = name[0];
    if (isalpha(first)){
        
        printf("%c", toupper(first));
    }
    
    //Print out the character following a space 
    for (int i = 0; i < strlen(name); i++){
        letter = name[i];
        next = name[i+1];
        
        if ((isspace(letter)) && (isalpha(next))){    
            printf("%c", toupper(next));
        }
    }
    printf("\n");
}
