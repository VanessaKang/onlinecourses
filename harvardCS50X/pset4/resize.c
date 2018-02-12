
/*
Name: Vanessa Kang
Course: Harvard Week 3
Challenge Name: Resize (less)
Purpose: Implement a program that resizes BMPs, per the below.

$ ./resize 4 small.bmp large.bmp

*/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main (int argc, char *argv[])
{
    //Ensure proper usage of running the file
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n inputfile outputfile\n");
        return 1;
    }
    //obtaining resize multiplication
    char * nString = *(argv + 1);
    //obtaining input file name
    char * inputfile = *(argv + 2);
    //obtaining output file name
    char * outputfile = *(argv + 3);
    //changing number string to integer string
    int n = atoi (nString);
    //Checks to make sure resize number is between 1 and 100
    if ((n > 100) || (n <= 0))
    {
        fprintf(stderr, "Please enter a number between 1 to 100\n");
        return 1;
    }
    //open input file for reading
    FILE* inputptr = fopen(inputfile, "r");

     //Check if inputfile is valid
     if (inputptr == NULL)
     {
         fprintf(stderr, "Input File: %s does not exist\n", inputfile);
         return 1;
     }

     //open output file for writing
     FILE* outputptr = fopen(outputfile, "w");

     //check if outputfile is valid
     if (outputptr == NULL)
    {
        fprintf(stderr, "Output File: %s does not Exists", outputfile);
        return 1;
    }

    //read inputfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bitfile;
    fread(&bitfile, sizeof(BITMAPFILEHEADER), 1, inputptr);
    //read inputfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bitinfo;
    fread(&bitinfo, sizeof(BITMAPINFOHEADER), 1, inputptr);

    //Checks if 24-bit uncompressed BMP 4.0
    if (bitfile.bfType != 0x4d42 || bitfile.bfOffBits != 54 ||
        bitinfo.biCompression != 0 || bitinfo.biBitCount != 24 || bitinfo.biSize != 40)
    {
        fclose(outputptr);
        fclose(inputptr);
        fprintf(stderr, "Unsupported file format. \n");
        return 1;
    }
    //Store padding in input file
    int inputpadding = (4 - (bitinfo.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //Store input file's height and width
    int oldWidth = bitinfo.biWidth;
    int oldHeight = bitinfo.biHeight;
    // Width of inputfile including padding (to be used for changing pointer BACK a scanline)
    int width = (sizeof(RGBTRIPLE) * bitinfo.biWidth) + inputpadding;

    //Resize width of image (not including padding) in pixels by mutiplication number given by user
    bitinfo.biWidth = bitinfo.biWidth * n;

    //determine the new outputfile's padding with the new biWidth
    int outputpadding = (4 - (bitinfo.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine the new height in pixels given by multiplication number given by user
    bitinfo.biHeight = bitinfo.biHeight * n;

    //Determine total size of image (in bytes)
    // = Size of Width (including padding) * height
    bitinfo.biSizeImage = (((sizeof(RGBTRIPLE) * bitinfo.biWidth) + outputpadding) * abs(bitinfo.biHeight));

    //File size of the bitmap file in bytes
    // This includes the image size and header files
    bitfile.bfSize = bitinfo.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //write modified FILE HEADER into output's BITMAPFILEHEADER
    fwrite(&bitfile, sizeof(BITMAPFILEHEADER), 1, outputptr);

    //write modified INFO HEADER into output's BITMAPINFOHEADER
    fwrite(&bitinfo, sizeof(BITMAPINFOHEADER), 1, outputptr);

    //iterate through each pixel row in input file
    for (int i = 0, biHeight = abs(oldHeight); i < (biHeight); i++)
    {
        //Make sure to copy each row n-1 times for resizing of the height vertically
        for (int recopy = 0; recopy < (n-1); recopy++)
        {
            //iterate through each pixel in scanline of inputfile
            for (int j = 0; j < oldWidth; j ++ )
            {

                //take the struct of the pixel colours
                RGBTRIPLE triple;

                //read RBG triple from inputfile
                fread(&triple, sizeof(RGBTRIPLE), 1, inputptr);

                //take pixel given and creates n copies horizontally for resizing
                for (int z = 0; z < n; z++)
                {
                    //write RBG triple n times
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outputptr);

                }
            }

            //skip over padding, if any in the input file
            fseek(inputptr, inputpadding, SEEK_CUR);

            // Add padding for output file
            for (int k = 0; k < outputpadding; k++)
            {
                fputc(0x00, outputptr);
            }

            //send inputfile cursor back width of input file to read same row again for new height
            fseek(inputptr, -width, SEEK_CUR);
        }

        //iterate through each pixel in scanline of the input file for the final row
        for (int j = 0; j < oldWidth; j ++ )
        {

            //take the struct of the pixel colours
            RGBTRIPLE triple;

            //read RBG triple from inputfile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputptr);

            //take pixel given and creates n copies horizontally for resizing
            for (int z = 0; z < n; z++)
            {
                //write RBG triple n times
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputptr);

            }
        }

        //skip over padding, if any from input file
        fseek(inputptr, inputpadding, SEEK_CUR);

        // add padding to output file scanline
        for (int k = 0; k < outputpadding; k++)
        {
            fputc(0x00, outputptr);
        }

    }

    // //close outputfile and inputfile
    fclose(inputptr);
    fclose(outputptr);

    return 0;
}
