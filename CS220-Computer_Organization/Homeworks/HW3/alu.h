/*
Header File for ALU HW Project
*/
#ifndef ALU_H
#define ALU_H

#include <stdint.h>

int nand(int a, int b);



// gates.c

int not(int a);
int and(int a, int b);
int or(int a, int b);
int xor(int a, int b);
int nor(int a, int b);
int xnor(int a, int b);
uint8_t bitwise_nand(uint8_t a, uint8_t b);
uint8_t bitwise_not(uint8_t a);
uint8_t bitwise_and(uint8_t a, uint8_t b);
uint8_t bitwise_or(uint8_t a, uint8_t b);
uint8_t bitwise_xor(uint8_t a, uint8_t b);
uint8_t bitwise_nor(uint8_t a, uint8_t b);
uint8_t bitwise_xnor(uint8_t a, uint8_t b);


// circuits.c

void half_adder(int a, int b, int *sum, int *carry);
void full_adder(int a, int b, int cin, int *sum, int *cout);
uint8_t ripple_add(uint8_t a, uint8_t b, int *overflow);


// alu.c

int mux(int sel, int a, int b);
uint8_t bitwise_mux(int sel, uint8_t a, uint8_t b);
uint8_t alu(uint8_t a, uint8_t b, int op1, int op0);

/* ALU opcodes */
#define ALU_ADD 0	/* op1=0, op0=0 */
#define ALU_AND 1 	/* op1=0, op0=1 */
#define ALU_OR  2	/* op1=1, op0=0 */
#define ALU_XOR 3	/* op1=1, op0=1 */

#endif /* ALU_H */
