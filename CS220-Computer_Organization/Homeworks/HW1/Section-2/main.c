/*
Main Driver to run:
Section 2: Color Images 
- Color Random Noise - Color Bitwise Pattern - Bit-Plane Color Extraction - Channel Fragmentation & Mixing

Written by Alex Ludwig
Feb 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/

#include <stdio.h>
#include "color_images.c"

#define WIDTH 256
#define HEIGHT 256
#define RGB 'B'
#define BITPLANE 0

int main(void){

    generate_randome_noise_color("section-2_pics/random_noise_color.ppm", WIDTH, HEIGHT);
    generate_rgb_pattern_1("section-2_pics/rgb_pattern_1.ppm", WIDTH, HEIGHT);
    generate_rgb_pattern_2("section-2_pics/rgb_pattern_2.ppm", WIDTH, HEIGHT);
    generate_rgb_pattern_3("section-2_pics/rgb_pattern_3.ppm", WIDTH, HEIGHT);

    //File labeling scheme: /{color}/ppm_output_image_{color}{bit}.ppm
    extract_color_bit_plane(
        "ppm_input_image.ppm", 
        "section-2_bit_plane_pics/blue/ppm_output_image_blue0.ppm", 
        RGB, BITPLANE
    ); 
    separate_channels("ppm_input_image.ppm", 
        "section-2_pics/red_only_output.ppm", 
        "section-2_pics/green_only_output.ppm",
        "section-2_pics/blue_only_output.ppm"
    );
    mix_channels("ppm_input_image_a.ppm", "ppm_input_image_b.ppm", "section-2_pics/mix_channels_output.ppm");


}