#include <stdio.h>
#include <cs50.h>


//Completed on: October 10, 2017 
//Purpose: Create two Mario half pyramids using hashes

int main (void)
{
    int height;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    //printf("  %i\n", height);
    for (int row = 0; row < height; row ++)
    {
        //printf("R%i", row );
        for (int space = 0; space < height - row - 1; space++)
        {
            //printf("S");
            printf(" ");
        }
        for (int hash = 0; hash < row + 1; hash++)
        {
            //printf("(%i)",hash);
            printf("#");
        }
        printf(" ");
        printf(" ");
        
        for (int hash = 0; hash < row + 1; hash++)
        {
            //printf("(%i)",hash);
            printf("#");
        }
        printf ("\n");
    }
}