/*
Main Driver to run:
Section 1: Black and White & Greyscale Images 
- Random Noise (BW and Greyscale) - Bit-Plane an Image - Bitwise Patterns 

Written by Alex Ludwig
Feb 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/

#include <stdio.h>

#include "black_and_white.c"

#define WIDTH 256
#define HEIGHT 256

//Changed to produce 0-7 bit extraction for pgm output
#define BITPLANE 0

int main(void){

    generate_random_noise_bw("section-1_pics/random_noise_bw.pgm", WIDTH, HEIGHT);
    generate_random_noise_grey("section-1_pics/random_noise_grey.pgm", WIDTH, HEIGHT);
    extract_bit_plane("pgm_input_image.pgm", "section-1_pics/pgm_output_image0.pgm", BITPLANE, WIDTH, HEIGHT);
    generate_xor_pattern("section-1_pics/xor_pattern.pgm", WIDTH, HEIGHT);
    generate_and_pattern("section-1_pics/and_pattern.pgm", WIDTH, HEIGHT);
    generate_or_pattern("section-1_pics/or_pattern.pgm", WIDTH, HEIGHT);
}