
/*
Name: Vanessa Kang
Course: Harvard Week 3
Challenge Name: Whodunit
Purpose: Answer some questions and then implement a program that reveals a hidden message in a BMP, per the below.

$ ./whodunit clue.bmp verdict.bmp

*/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main (int argc, char *argv[])
{
    //Ensure proper file of running the file
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit inputfile outputfile");
        return 1;
    }

    char * inputfile = *(argv + 1);
    char * outputfile = *(argv + 2);

    //open input file for reading
    FILE* inputptr = fopen(inputfile, "r");

    //Check if inputfile is valid
    if (inputptr == NULL)
    {
        fprintf(stderr, "Input File: %s does not exist\n", inputfile);
        return 2;
    }

    //open output file for writing
    FILE* outputptr = fopen(outputfile, "w");

    //check if outputfile is valid
    if (outputptr == NULL)
    {
        fprintf(stderr, "Output File: %s does not Exists", outputfile);
        return 3;
    }

    //read inputfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bitfile;
    fread(&bitfile, sizeof(BITMAPFILEHEADER), 1, inputptr);

    //read inputfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bitinfo;
    fread(&bitinfo, sizeof(BITMAPINFOHEADER), 1, inputptr);

    //24-bit uncompressed BMP 4.0
    if (bitfile.bfType != 0x4d42 || bitfile.bfOffBits != 54 ||
        bitinfo.biCompression != 0 || bitinfo.biBitCount != 24 || bitinfo.biSize != 40)
    {
        fclose(outputptr);
        fclose(inputptr);
        fprintf(stderr, "Unsupported file format. \n");
        return 4;
    }

    //write into output's BITMAPFILEHEADER
    fwrite(&bitfile, sizeof(BITMAPFILEHEADER), 1, outputptr);

    //write into output's BITMAPINFOHEADER
    fwrite(&bitinfo, sizeof(BITMAPINFOHEADER), 1, outputptr);

    //determine padding for scanlines
    int padding = (4 - (bitinfo.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //iterate through each pixel row
    for (int i = 0, biHeight = abs(bitinfo.biHeight); i < biHeight; i++)
    {
        //iterate through each pixel in scanline
        for (int j = 0; j < bitinfo.biWidth; j ++ )
        {

            //take the struct of the pixel colours
            RGBTRIPLE triple;

            //read RBG triple from inputfile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputptr);

            //if the pixel is not red, turn it black
            if ((triple.rgbtRed != 0xff) && (triple.rgbtBlue != 0x0) && (triple.rgbtGreen != 0x0)){
                triple.rgbtBlue = 0x0;
                triple.rgbtGreen = 0x0;
                triple.rgbtRed = 0x0;
            }
            //if pixel is red, make it white
            if ((triple.rgbtRed == 0xff) && (triple.rgbtBlue == 0x0) && (triple.rgbtGreen == 0x0)){
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtRed = 0xff;
            }


            //write RBG triple from outputfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputptr);
        }

        //skip over padding, if any
        fseek(inputptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputptr);
        }

    }

    //close outputfile and inputfile
    fclose(inputptr);
    fclose(outputptr);

    return 0;
}
