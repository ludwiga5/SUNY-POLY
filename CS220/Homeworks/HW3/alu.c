/*
Section 3: Multiplexer and ALU

Written by Alex Ludwig
April 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/
#include "alu.h"

int mux(int sel, int a, int b)
{
	return(or(and(not(sel),a),and(sel,b)));
}

uint8_t bitwise_mux(int sel, uint8_t a, uint8_t b) {
    uint8_t result = 0;
    for (int i = 0; i < 4; ++i) {
        int aBit = bitwise_and((a >> i), 1);
        int bBit = bitwise_and((b >> i), 1);
        int rBit = mux(sel, aBit, bBit);
        result = bitwise_or(result, (rBit << i));
    }
    return result;
}

uint8_t alu(uint8_t a, uint8_t b, int op1, int op0)
{
	int overflow;
	uint8_t ADD = ripple_add(a, b, &overflow);
	uint8_t AND = bitwise_and(a, b);
	uint8_t OR  = bitwise_or(a, b);
	uint8_t XOR = bitwise_xor(a, b);

	uint8_t res0 = bitwise_mux(op0, ADD, AND);
	uint8_t res1 = bitwise_mux(op0, OR,  XOR);
	
	uint8_t resFinal = bitwise_mux(op1, res0, res1);
	
	return resFinal;
}
