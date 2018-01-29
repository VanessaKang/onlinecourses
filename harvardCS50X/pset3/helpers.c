// Helper functions for music

/*

Name: Vanessa Kang
Course: Harvard Week 2
Challenge Name: helpers.c
Purpose: Implement functions that can calculate the frequency of music notes on a piano.
            Determine duration of music notes in eigths and determine if there is a rest.
            These functions will be used to read music notes off a txt file and output
            sounds using the frequency I just created to play music.

*/

#include <cs50.h>
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <math.h>



// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //Index to get the numerator and denominator from fraction string
    char charNumerator = fraction[0];
    char charDenominator = fraction[2];
    //Change those characters into ascii numbers of what they represent:  '1' - '0' = 1 integer
    int num = charNumerator - '0';
    int den = charDenominator - '0';
    //Obtain number of eighths in the music note
    int eighthsNum = ((8 * num) / den) ;
    return eighthsNum;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    char accidental = '\0';
    int octave;
    //if there is accidentals included in notes
    if (strlen(note) == 3)
    {
        //Extract Letter as char
        letter = note[0];
        //Extract Accidental as char
        accidental = note[1];
        //Extract Octave as Integer
        char strOctave = note[2];
        octave = strOctave - '0';
    }
    //If there is no accidentals included in notes
    else
    {
        //Extract Letter note as Char
        letter = note[0];
        //Extract octave as Integer
        char strOctave = note[1];
        octave = strOctave - '0';
    }
    //Define exponent variable for A4 frequency formula : 440 ^ (n/12)
    double n = 0.0;
    //Initialize n based on letter on piano (calculated by distance away from A)
    if (letter == 'B')
    {
        n = 2;
    }
    else if (letter == 'G')
    {
        n = -2;
    }
    else if (letter == 'F')
    {
        n = -4;
    }
    else if (letter == 'E')
    {
        n = -5;
    }
    else if (letter == 'D')
    {
        n = -7;
    }
    else if (letter == 'C')
    {
        n = -9;
    }
    //Move n up or down one semi-tone based on accidental
    if (accidental == '#')
    {
        n += 1;
    }
    else if (accidental == 'b')
    {
        n -= 1;
    }
    //Modify n to account for piano notes on a different octave
    n += (octave - 4) * 12;
    //Apply formula for Frequency of Piano notes: 440^(n/12)
    double noteFrequency = 440.0 * pow(2.0, n / 12);
    //Round to the nearest Integer
    noteFrequency = round(noteFrequency);
    return noteFrequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // get_string() returns "" when there is a new line or an "enter" from the user
    if (strcmp(s, "") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}