#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Purpose: Determine the least amount of coins needed to give change
//Completed: October 10, 2017
//Revised: January 21, 2018

int main(void){
    float dollar;
    do{
        printf("Change is owed?: ");
        dollar = get_float();
    }
    while (dollar < 0);

    // CONVERT DOLLARS INTO CENTS, FLOAT -> INT + ROUNDED
    int cents = round(dollar*100);

    int count = 0;

    //Check if the change can be given in quarters
    if (cents/25 >= 1){
        count = count + cents/25;
        cents = cents%25;
    }

    //Check if remaining change can be given in dimes
    if (cents/10 >= 1){
        count = count + cents/10;
        cents = cents%10;
    }

    //Check if remaining change can be given in nickels
    if (cents/5 >= 1){
        count = count + cents/5;
        cents = cents%5;
    }

    //Check if remaining change can be given in pennies
    if (cents/1 >= 1){
        count = count + cents/1;
        cents = cents%1;
    }

    //Print the amount of coins given back to user
    printf("%i\n", count);

}
