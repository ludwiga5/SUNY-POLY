/*
Section 2: Arithmetic Circuits

Written by Alex Ludwig
March 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/
#include "alu.h"
#include "gates.c"

void half_adder(int a, int b, int *sum, int *carry)
{
	*carry = and(a, b);
	*sum  = xor(a, b);
}

void full_adder(int a, int b, int cin, int *sum, int *cout)
{
	int s1, c1, S, c2;
	half_adder(a, b, &s1, &c1);
	half_adder(s1, cin, &S, &c2);
	*cout = or(c1, c2);
	*sum  = S;
}

uint8_t ripple_add(uint8_t a, uint8_t b, int *overflow)
{
    int s1, s2, s3, s4, C;
	uint8_t sum = 0b0000;
	full_adder((a>>0)&1, (b>>0)&1, 0, &s1, &C);
	full_adder((a>>1)&1, (b>>1)&1, C, &s2, &C);
	full_adder((a>>2)&1, (b>>2)&1, C, &s3, &C);
	full_adder((a>>3)&1, (b>>3)&1, C, &s4, &C);
	*overflow = C;
	sum |= (s1 << 0);
	sum |= (s2 << 1);
	sum |= (s3 << 2);
	sum |= (s4 << 3);
	return sum;
}
