#include <stdio.h>
#include <cs50.h>

//Purpose: Determine the number of water bottle used to take a shower based on minutes

int main (void){
    printf("Minutes: ");
    unsigned int showertime = get_int();
    printf("Bottles: %i\n", showertime * (192/16) ); 
}