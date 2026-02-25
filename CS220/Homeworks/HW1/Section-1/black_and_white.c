/*
House, but not run
Section 1: Black and White & Greyscale Images 
- Random Noise (BW and Greyscale) - Bit-Plane an Image - Bitwise Patterns 

Written by Alex Ludwig
Feb 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//  Prototypes
void generate_random_noise_bw(const char* filename, int width, int height);
void generate_random_noise_grey(const char* filename, int width, int height);
void extract_bit_plane(const char* input_file, const char* output_file, int bit_position, int width, int height);
void generate_xor_pattern(const char* filename, int width, int height);
void generate_and_pattern(const char* filename, int width, int height);
void generate_or_pattern(const char* filename, int width, int height);

/*
Task 1
Generates random black & white noise images
*/
void generate_random_noise_bw(const char* filename, int width, int height){
 
    /*
    Open {filename} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    /*
    Write PGM header
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    /*
    Random number ({0,1} * 255) for black & white
    Loops height*width number of times to fill output
    */
    int ran_bin;
    srand(time(NULL));
    for(int i = 0; i<height*width; i++){
        ran_bin = ((rand() % 0b10)+0)*0xFF;
        fwrite(&ran_bin, 1, 1, file);
    }

    /*
    Closing the Barn Door behind me
    */
    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}  void generate_random_noise_grey(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    /*
    Write PGM header
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    /*
    Random number (0-255) for black & white
    Loops height*width number of times to fill output
    */
    int ran_bin;
    srand(time(NULL));
    for(int i = 0; i<height*width; i++){
        ran_bin = (rand() % 0x100);
        fwrite(&ran_bin, 1, 1, file);
    }

    /*
    Closing the Barn Door behind me
    */
    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}

/*
Task 2
Bit-Plane Extraction
*/
void extract_bit_plane(
    const char* input_file, const char* output_file, 
    int bit_position,
    int height, int width){

    /*
    Open {input_file} to read
    In binary mode - "rb"
    Open {output_file} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *input = fopen(input_file, "rb");
    if (!input) {
        printf("Error opening file: %s!\n", input_file);
        return;
    }
    FILE *output = fopen(output_file, "wb");
    if (!output) {
        printf("Error opening file: %s!\n", output_file);
        return;
    }



    /*
    Run an input file to "Read" and ignore header information from input files
    Reset width and height with information
    "# Created by GIMP version 2.10.36 PNM plug-in" Necessary to remove comment in ppm header
    */
    fscanf(input, "P5\n# Created by GIMP version 2.10.36 PNM plug-in\n%d %d\n255\n",&width, &height);
    /*
    Write PGM header for Output File
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(output, "P5\n%d %d\n255\n", width, height);

    /*
    Then Give the value of a bit at $bit_position assignes a pixel value for output_file
    */
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char pixel = fgetc(input);
            pixel = pixel >> bit_position;
            pixel = pixel & 1;
            pixel *= 0xff;

            fwrite(&pixel, 1, 1, output);

        }
    }


    fclose(input);
    printf("Created %s %d %d", output_file, 256, 256);
    fclose(output);
}

/*
Task 3
Bitwise Pattern Generation
*/
void generate_xor_pattern(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file: %s!\n", filename);
        return;
    }

    /*
    Write PGM header
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    /*
    Assigns each pixel x xor y value
    */
    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char pixel = x ^ y;
            fwrite(&pixel, 1, 1, file);

        }
    }

    /*
    Closing the Barn Door behind me
    */
    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}  void generate_and_pattern(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file: %s!\n", filename);
        return;
    }

    /*
    Write PGM header
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    /*
    Assigns each pixel x xor y value
    */
    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char pixel = x & y;
            fwrite(&pixel, 1, 1, file);

        }
    }

    /*
    Closing the Barn Door behind me
    */
    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}  void generate_or_pattern(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    Return if error occurs
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file: %s!\n", filename);
        return;
    }

    /*
    Write PGM header
    P5 - Binary grayscale
    255 - Max Color Value (White)
    */
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    /*
    Assigns each pixel x xor y value
    */
    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char pixel = x | y;
            fwrite(&pixel, 1, 1, file);

        }
    }

    /*
    Closing the Barn Door behind me
    */
    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}
