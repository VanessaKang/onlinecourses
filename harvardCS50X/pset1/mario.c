#include <stdio.h>
#include <cs50.h>


//Completed on: October 10, 2017
//Purpose: Create two Mario half pyramids using hashes

int main (void)
{
    int height;
    //Makes sure to ask User for Height atleast once and will continue to ask unless user gives height between 0 and 23
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);

    //Builds mario row of pyramids by user's defined height
    for (int row = 0; row < height; row ++)
    {
        //Adds spaces to the pyramid
        for (int space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        //Adds hashes to the pyramid
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }
        //prints double spaces for the other side of pyramid
        printf(" ");
        printf(" ");
        //Creates other side of hashes and mirrored
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }
        printf ("\n");
    }
}
