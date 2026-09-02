/*
Section 1: Logic Gates

Written by Alex Ludwig
March 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/

#include "alu.h"


int nand(int a, int b)
{
	return !(a & b);
}

int not(int a)
{
	return nand(a, a);
}

int and(int a, int b)
{
	int initialNAND = nand(a, b);
	return nand(initialNAND, initialNAND);
}

int or(int a, int b)
{
	return nand(nand(a, a), nand(b, b));
}

int xor(int a, int b)
{
	int initialNAND = nand(a, b);
	return nand(nand(a, initialNAND), nand(initialNAND, b));
}

int nor(int a, int b)
{
	int initialOR = or(a, b);
	return nand(initialOR, initialOR);
}

int xnor(int a, int b)
{
	int initialXOR = xor(a, b);
	return nand(initialXOR, initialXOR);
}

//Bitwise Functions

uint8_t bitwise_nand(uint8_t a, uint8_t b) {
    int b0 = nand(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = nand(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = nand(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = nand(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_not(uint8_t a) {
    int b0 = not(and(a >> 0, 1));
    int b1 = not(and(a >> 1, 1));
    int b2 = not(and(a >> 2, 1));
    int b3 = not(and(a >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_and(uint8_t a, uint8_t b) {
    int b0 = and(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = and(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = and(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = and(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_or(uint8_t a, uint8_t b) {
    int b0 = or(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = or(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = or(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = or(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_xor(uint8_t a, uint8_t b) {
    int b0 = xor(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = xor(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = xor(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = xor(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_nor(uint8_t a, uint8_t b) {
    int b0 = nor(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = nor(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = nor(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = nor(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}

uint8_t bitwise_xnor(uint8_t a, uint8_t b) {
    int b0 = xnor(and(a >> 0, 1), and(b >> 0, 1));
    int b1 = xnor(and(a >> 1, 1), and(b >> 1, 1));
    int b2 = xnor(and(a >> 2, 1), and(b >> 2, 1));
    int b3 = xnor(and(a >> 3, 1), and(b >> 3, 1));
    return (b3 << 3) + (b2 << 2) + (b1 << 1) + b0;
}