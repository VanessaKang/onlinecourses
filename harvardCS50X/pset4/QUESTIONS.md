###Harvard PSET4
###Questions for whodunit
###Week 3

# Questions

## What's `stdint.h`?

stdint.h is a header file that specifies exact width integers. It defines the maximum and minimum for the exact type. Example includes int8_t or uint64_t. This header file also has functions that
has the ability for users to manipulate hardward I/O.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

This helps define the size of the integer and the range of values that it can hold. This is especially good for filling in exact number of data in bitmap headers.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte, DWORD = 4 bytes, LONG = 4 bytes and WORD = 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes is field bfType which is used to identify a BMP and DIB file . In Hexadecimal the first two bytes is 0x42 0x4D. In addition, the first 2 bytes of the BMP file format can also
be interpreted in ASCII encoding as the character "B" then the character "M".

## What's the difference between `bfSize` and `biSize`?

bfSize stands for the size of the BMP file in bytes.
BiSize stands for the size of the header in bytes.

## What does it mean if `biHeight` is negative?

 If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner.
 If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
 Source: MDSN

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits
that define each pixel and the maximum number of colors in the bitmap. For smiley.bmp this value is 24
which means that each 3-byte triplet in the bitmap array represents the relative
intensities of blue, green, and red, respectively, for a pixel.
Source: MDSN

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Fopen may return NULL because the file may not exist or there is an error with opening the file.

## Why is the third argument to `fread` always `1` in our code?

The third argument of fread stands for how many times it will read a specified size (size specified in second argument)
to the user. In the code, the size that was specified in the second argument is the size of the struct (e.g. sizeof(BITMAPFILEHEADER))
which is enough to be only read in once.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

In line 63, copy.c determines the padding for scanlines (row) from equation (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4.
Since RBGTRIPLE is 3 and bi.Width is 3 then padding is 3.

## What does `fseek` do?

The pointer sequentially reads from the start to the end of the file. fseek allows you to change the offset of the file pointer
which allows the user to go to any location in the file.

## What is `SEEK_CUR`?

The purpose of seek_cur is to change the location of the file pointer (apply offset) from its current location.
