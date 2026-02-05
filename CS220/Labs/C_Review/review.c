#include <stdio.h>

int main(void){

    /*
    What's Printable?
    https://www.asciitable.com
    */
    char c_value = 'p';
    int i_value = 123;          //Unsigned removes negative values
    float f_value = 1.618;      //Real Numbers
    double d_value = 3.1415926; //Real Numbers w/double the amount of precision

    printf("c_value: %c\n", c_value);
    printf("\tit takes up %d bytes\n", sizeof(c_value));
    printf("\tits binary representation is %b\n\n", c_value);

    printf("i_value: %d\n", i_value);
    printf("\tit takes up %d bytes\n\n", sizeof(i_value));
    printf("\tits binary representation is %b\n\n", i_value);

    printf("f_value: %f\n", f_value);
    printf("\tit takes up %d bytes\n\n", sizeof(f_value));
    printf("\tits binary representation is %b\n\n", f_value);

    printf("d_value: %lf\n", d_value);
    printf("\tit takes up %d bytes\n\n", sizeof(d_value));
    printf("\tits binary representation is %b\n\n", d_value);    

    return 0;
}
