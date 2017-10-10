#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Purpose: Determine the least amount of coins needed to give change 
//Completed: October 10, 2017

int main(void){
    float dollar;
    printf("O hai!");
    do{
        printf("How much change is owed?\n");
        dollar = get_float();
    }
    while (dollar < 0);
    
    // CONVERT DOLLARS INTO CENTS, FLOAT -> INT + ROUNDED
    int cents = round(dollar*100); 
    //printf("%i\n", cents);
    
    //float change = round(centchange);
    //printf("%f\n", change );
    //float n = printf("%.2f\n", change);
    //printf("HELLO%f\n", n); 
    //--------------------------------------------
    int count = 0;

    if (cents/25 >= 1){
        count = count + cents/25; 
        cents = cents%25;
    }
    
    //printf("FIRST%i\n",count);
    //printf("FIRST%i\n",cents);
    
    if (cents/10 >= 1){
        count = count + cents/10; 
        cents = cents%10;
    }
    //printf("Second%i\n",count);
    //printf("Second%i\n",cents);
    
    if (cents/5 >= 1){
        count = count + cents/5; 
        cents = cents%5;
    }
    
    //printf("Third%i\n",count);
    //printf("Third%i\n",cents);
    
    if (cents/1 >= 1){
        count = count + cents/1; 
        cents = cents%1;
    }
    
    //printf("Last%i\n",count);
    //printf("Last%i\n",cents);
    
    printf("%i\n", count);
    
}