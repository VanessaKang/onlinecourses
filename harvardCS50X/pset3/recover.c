
/*
Name: Vanessa Kang
Course: Harvard Week 4
Challenge Name: Recover
Purpose: Implement a program that recovers JPEGs from a forensic image, per the below

$ ./recover card.raw

*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

int main(int argc, char * argv[])
{
    //Checks for correct Usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    //Obtains the card.raw file
    char * image = *(argv + 1);

    //Opens the memory card raw file
    FILE* memcardptr = fopen(image, "r");

    //Checks if memcardptr file can be opened or not
    if (memcardptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }

    //JPEG Files Identifiers are Displayed in Bytes (e.g. 0xFF 0xd8) so BYTES is used to store data correctly
    BYTE buffer[512] = {0};
    //jpegWriting will keep track if a jpeg file is currently being written out
    int jpegWriting = false; // FALSE
    //Keeps track of the number of JPEGs found
    int jpegcount = 0;
    //Initalizes filename of 8 characters (e.g. 000.jpg + '\0')
    char filename[8];
    //Initializes jpegfileptr
    FILE* jpegfileptr = NULL;

    //Reads in initial 512 bytes from memory card file
    int num = fread(buffer, 512, 1, memcardptr);

    //As long as its not EOF
    while (num)
    {
        //Check if the start of a jpeg is found
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            //If currently writing in a JPEG file
            //The start of another JPEG FILE means that previous file needs to close and new file needs to open
            if (jpegWriting == true)
            {
                //Close previous jpegfile
                fclose(jpegfileptr);

                //Create incrementing filename for each JPEG (based off jpegcount)
                sprintf(filename, "%03i.jpg", jpegcount);

                //Open a JPEG File to write in
                jpegfileptr = fopen(filename, "w");

                //Write the 512 Buffer we just analyzed
                fwrite(buffer, 512, 1, jpegfileptr);

                //Read the next set of 512 bytes from the memcardptr
                num = fread(buffer, 512, 1, memcardptr);

                //Increments the jpegcount
                jpegcount++;
            }

            //if currently not writing in a jpeg file (jpegWriting == 0)
            //Make sure to open a file to write JPEG data into it
            else if (jpegWriting == false)
            {
                //Indicate that a jpeg has been found
                jpegWriting = true;

                //Create incrementing filename for each JPEG (based off jpegcount)
                sprintf(filename, "%03i.jpg", jpegcount);

                //Open a JPEG File to write in
                jpegfileptr = fopen(filename, "w");

                //Write the 512 Buffer we just analyzed
                fwrite(buffer, 512, 1, jpegfileptr);

                //Read the next set of 512 bytes from the memcardptr
                num = fread(buffer, 512, 1, memcardptr);

                //Increments the jpegcount
                jpegcount ++;
            }

        }

        //If Currently writing in a JPEG file, keep writing data in
        if (jpegWriting == true)
        {
            //Write the 512 Buffer we just analyzed
            fwrite(buffer, 512, 1, jpegfileptr);

            //Read the next set of 512 bytes from the memcardptr
            num = fread(buffer, 512, 1, memcardptr);
        }

        //If JPEG file header not found and currently not writing into a file, then skip previous data and read next set of data
        else
        {
            //Read the next set of 512 bytes from the memcardptr
            num = fread(buffer, 512, 1, memcardptr);
        }
    }

    //Close memory card file and jpeg writer pointer
    fclose(memcardptr);
    fclose(jpegfileptr);
    return 0;
}
