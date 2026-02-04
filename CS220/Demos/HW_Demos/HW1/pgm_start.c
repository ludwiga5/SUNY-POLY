#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Image dimensions
    int width = 256;
    int height = 256;
    
    // Open file for writing in binary mode
    FILE *file = fopen("output.pgm", "wb");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Write PGM header (P5 = binary grayscale)
    fprintf(file, "P5\n%d %d\n255\n", width, height);
    
    // Greyscale gradient pattern for each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char pixel = x;

            fwrite(&x, 1, 1, file);
        }
    }
    
    fclose(file);
    printf("Created output.pgm (%dx%d)\n", width, height);
    
    return 0;
}