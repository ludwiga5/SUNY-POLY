/*
House but not run
Section 2: Color Images 
- Color Random Noise - Color Bitwise Pattern - Bit-Plane Color Extraction - Channel Fragmentation & Mixing

Written by Alex Ludwig
Feb 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototypes
void generate_random_noise_color(const char* filename, int width, int height);
void generate_rgb_pattern_1(const char* filename, int width, int height);
void generate_rgb_pattern_2(const char* filename, int width, int height);
void generate_rgb_pattern_3(const char* filename, int width, int height);
void extract_color_bit_plane(const char* input_file, const char* output_file, char channel, int bit_position);
void separate_channels(const char* input_file, const char* r_out, const char* g_out, const char* b_out);
void mix_channels(const char* input_file_a, const char* input_file_b, const char* output_file);

/*
Task 1
Generated random color noise images
*/
void generate_randome_noise_color(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening %s!\n", filename);
        return;
    }

    /*
    Write PPM header
    P6 - Binary Color
    255 - Max Color Value
    */
    fprintf(file, "P6\n%d %d\n255\n", width, height);

    /*
    Random number ({0,1} * {MaxColorValue} ) for each Red, Green, & Blue value
    Loops height * width number * 3 (RGB Values) of times to fill output
    */
    int ran_bin;
    srand(time(NULL));
    for(int i = 0; i<height*width*3; i++){
        ran_bin = (rand() % 2)*0xFF;
        fwrite(&ran_bin, 1, 1, file);
    }

    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}

/*
Task 2
Bitwise Color Patterns
*/
void generate_rgb_pattern_1(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening %s!\n", filename);
        return;
    }

    /*
    Write PPM header
    P6 - Binary Color
    255 - Max Color Value
    */
    fprintf(file, "P6\n%d %d\n255\n", width, height);


    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char R = (x^y)|~(x^y) & 0xFF;
            unsigned char G = (x^~y)|(x&~y) & 0xFF;
            unsigned char B = ((x&y)|(~x^y|y)) & 0xFF;

            fwrite(&R, 1, 1, file);
            fwrite(&G, 1, 1, file);
            fwrite(&B, 1, 1, file);

        }
    }

    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

} void generate_rgb_pattern_2(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening %s!\n", filename);
        return;
    }

    /*
    Write PPM header
    P6 - Binary Color
    255 - Max Color Value
    */
    fprintf(file, "P6\n%d %d\n255\n", width, height);


    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char R = ~((x^~y)&(x<<y^x)) & 0xFF;
            unsigned char G = (x<<y)&(x|y) & 0xFF;
            unsigned char B = (x&y)|(x^y) & 0xFF;

            fwrite(&R, 1, 1, file);
            fwrite(&G, 1, 1, file);
            fwrite(&B, 1, 1, file);

        }
    }

    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

} void generate_rgb_pattern_3(const char* filename, int width, int height){

    /*
    Open {filename} to write
    In binary mode - "wb"
    */
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    /*
    Write PPM header
    P6 - Binary Color
    255 - Max Color Value
    */
    fprintf(file, "P6\n%d %d\n255\n", width, height);


    for(int y = 0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char R = (y<<(x+y)) & 0xFF;
            unsigned char G = (x&y) & 0xFF;
            unsigned char B = (x|y<<x) & 0xFF;

            fwrite(&R, 1, 1, file);
            fwrite(&G, 1, 1, file);
            fwrite(&B, 1, 1, file);

        }
    }

    fclose(file);
    printf("Created %s (%dx%d)\n", filename, width, height);
    
    return;

}

/*
Task 3
Bit-Plane Color Extraction
*/
void extract_color_bit_plane(const char* input_file, const char* output_file, char channel, int bit_position){

    int height, width;
    /*
    Open {input_file} to read
    In binary mode - "rb"
    Open {output_file} to write
    In binary mode - "wb"
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
    Scan an input file to "Read" and ignore header information from input files
    Set width and height information from header
    "# Created by GIMP version 2.10.36 PNM plug-in" Necessary to remove comment in ppm header
    */
    fscanf(input, "P6\n# Created by GIMP version 2.10.36 PNM plug-in\n%d %d\n255\n",&width, &height);
    /*
    Write PPM header for Output File
    P6 - Binary color
    255 - Max Color Value
    */
    fprintf(output, "P6\n%d %d\n255\n", width, height);


    /*
    Using conditions to determine which loop to cycle through
    Mulitple loops written to minimize checking the channel
    through each loop iteration
    */

    //This variable is used with fgetc to bypass unused 
    //color bytes when reading input ppm
    unsigned char byte_pass;

    //Looping for Red Channel
    if(channel == 'R'){
        unsigned char R;
        unsigned char G = 0;
        unsigned char B = 0; 
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){

                unsigned char R = fgetc(input);
                R = R >> bit_position;
                R = R & 1;
                R *= 0xFF;
                fwrite(&R, 1, 1, output);

                //bypass G B bytes
                byte_pass = fgetc(input);
                byte_pass = fgetc(input);
                fwrite(&G, 1, 1, output);
                fwrite(&B, 1, 1, output);

            }
        }
    }  
    //Looping for Green Channel
    else if(channel == 'G'){
        unsigned char R = 0;
        unsigned char G;
        unsigned char B = 0; 
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){

                //bypass Red byte
                byte_pass = fgetc(input);
                fwrite(&R, 1, 1, output);

                //get Green byte and adjust bit position
                unsigned char G = fgetc(input);
                G = G >> bit_position;
                G = G & 1;
                G *= 0xFF;
                fwrite(&G, 1, 1, output);

                //bypass Blue byte
                byte_pass = fgetc(input);
                fwrite(&B, 1, 1, output);

            }
        }
    }
    //Looping for Blue Channel
    else if(channel == 'B'){
        unsigned char R = 0;
        unsigned char G = 0;
        unsigned char B; 
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){

                //bypass Red & Green Bytes
                byte_pass = fgetc(input);
                byte_pass = fgetc(input);
                fwrite(&R, 1, 1, output);
                fwrite(&G, 1, 1, output);

                unsigned char B = fgetc(input);
                B = B >> bit_position;
                B = B & 1;
                B *= 0xFF;

                fwrite(&B, 1, 1, output);

            }
        }
    } 
    //Error handling for channel selection
    else{
        printf("Error: Incorrect specification of channel R, G, B\n");
        return;
    }

    fclose(input);
    printf("Created %s (%dx%d)\n", output_file, width, height);
    fclose(output);

    return;

}


/*
Task 4
Channel Fragmentation & Mixing
*/
void separate_channels(const char* input_file, const char* r_out, const char* g_out, const char* b_out){

    int width, height;
    /*
    Open {input_file} to read
    In binary mode - "rb"
    Open {output_file}s to write
    In binary mode - "wb"
    */
    FILE *input = fopen(input_file, "rb");
    if (!input) {
        printf("Error opening file: %s!\n", input_file);
        return;
    }
    FILE *red_output = fopen(r_out, "wb");
    if (!red_output) {
        printf("Error opening file: %s!\n", r_out);
        fclose(input);
        return;
    }
    FILE *green_output = fopen(g_out, "wb");
    if (!green_output) {
        printf("Error opening file: %s!\n", g_out);
        fclose(input);
        fclose(red_output);
        return;
    }
    FILE *blue_output = fopen(b_out, "wb");
    if (!blue_output) {
        printf("Error opening file: %s!\n", b_out);
        fclose(input);
        fclose(red_output);
        fclose(green_output);
        return;
    }
    /*
    Scan an input file to "Read" and ignore header information from input files
    Adjust width and height
    "# Created by GIMP version 2.10.36 PNM plug-in" Necessary to remove comment in ppm header
    */
    fscanf(input, "P6\n# Created by GIMP version 2.10.36 PNM plug-in\n%d %d\n255\n",&width, &height);
    /*
    Write PPM header for Output File
    P6 - Binary color
    255 - Max Color Value
    */
    fprintf(red_output, "P6\n%d %d\n255\n", width, height);
    fprintf(green_output, "P6\n%d %d\n255\n", width, height);
    fprintf(blue_output, "P6\n%d %d\n255\n", width, height);

    //Used to fill RGB values for empty channels
    unsigned char no_color = 0;

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){

            unsigned char R = fgetc(input);
            unsigned char G = fgetc(input);
            unsigned char B = fgetc(input);

            //Writes 
            fwrite(&R, 1, 1, red_output);
            fwrite(&no_color, 1, 1, red_output);
            fwrite(&no_color, 1, 1, red_output);

            fwrite(&no_color, 1, 1, green_output);
            fwrite(&G, 1, 1, green_output);
            fwrite(&no_color, 1, 1, green_output);

            fwrite(&no_color, 1, 1, blue_output);
            fwrite(&no_color, 1, 1, blue_output);
            fwrite(&B, 1, 1, blue_output);

        }
    }

    fclose(input);

    fclose(red_output);
    printf("Created %s (%dx%d)\n", r_out, width, height);
    fclose(green_output);
    printf("Created %s (%dx%d)\n", g_out, width, height);
    fclose(blue_output);
    printf("Created %s (%dx%d)\n", b_out, width, height);

    return;

} void mix_channels(const char* input_file_a, const char* input_file_b, const char* output_file){

    int height, width;
    /*
    Open {input_file}s to read
    In binary mode - "rb"
    Open {output_file} to write
    In binary mode - "wb"
    */
    FILE *inputA = fopen(input_file_a, "rb");
    if (!inputA) {
        printf("Error opening file: %s!\n", input_file_a);
        return;
    }
    FILE *inputB = fopen(input_file_b, "rb");
    if(!inputB){
        printf("Error opening file %s!\n", input_file_b);
        fclose(inputA);
        return;
    }
    FILE *output = fopen(output_file, "wb");
    if (!output) {
        printf("Error opening file: %s!\n", output_file);
        fclose(inputA);
        fclose(inputB);
        return;
    }

    /*
    Run an input file to "Read" and ignore header information from input files
    Adjust width and height
    "# Created by GIMP version 2.10.36 PNM plug-in" Necessary to remove comment in ppm header
    */
    fscanf(inputA, "P6\n%d %d\n255\n",&width, &height);
    fscanf(inputB, "P6\n%d %d\n255\n",&width, &height);
    /*
    Write PPM header for Output File
    P6 - Binary color
    255 - Max Color Value
    */
    fprintf(output, "P6\n%d %d\n255\n", width, height);


    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            //Runs 3 times for RGB
            for(int i=0; i<3; i++){

                unsigned char pixelA = fgetc(inputA);
                unsigned char pixelB = fgetc(inputB);
                unsigned char pixel_output = pixelA ^ pixelB;
                fwrite(&pixel_output, 1, 1, output);
            
            }

        }
    }

    fclose(inputA);
    fclose(inputB);
    fclose(output);
    printf("Created %s (%dx%d)\n", output_file, width, height);
    
    return;

}