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
