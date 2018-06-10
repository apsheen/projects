/**
 * scale.c
 *
 * CS50 AP
 * Scale
 *
 * Resizes a BMP.
 **/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./scale <times you want the image to be enlarged> infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //remember how much to enlarge
    int times = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //copy the file header and info header
    BITMAPFILEHEADER outfile_f = bf;
    BITMAPINFOHEADER outfile_i = bi;
    
    //scale up width and height
    outfile_i.biWidth = bi.biWidth * times;
    outfile_i.biHeight = bi.biHeight * times; //must use absolute value or else will get overflow
    
    // determine padding for scanlines for outfile
    int padding = (4 - (outfile_i.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change size of image and file, respectively
    outfile_i.biSizeImage = abs(outfile_i.biHeight) * ((outfile_i.biWidth * sizeof(RGBTRIPLE)) + padding);
    outfile_f.bfSize = outfile_i.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outfile_f, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outfile_i, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        long offset = ftell(inptr);
        
        for (int j = 0; j < times; j++) //vertical scaling
        {
            fseek(inptr, offset, SEEK_SET);
            
            //iterate over pixels in scanline
            for (int k = 0; k < abs(bi.biWidth); k++)
            {
                //temporary storage
                RGBTRIPLE triple;
                
                //read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                //write RGB triple to outfile as many times as needed
                for(int l = 0; l < times; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
    
            // skip over padding, if any
            fseek(inptr, old_padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }
                
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}