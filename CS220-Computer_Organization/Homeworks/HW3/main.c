/*
Section 4: Testing for all gates, circuits, and alu testing

Written by Alex Ludwig
April 2026
Language: C
Apple clang version 17.0.0 (clang-1700.4.4.1)
Target: arm64-apple-darwin24.6.0
*/
#include <stdio.h>
#include <stdint.h>
#include "alu.h"


int main(void)
{
	//Pt1 Gate Truth Tables
	printf("=== Part 1: Gate Truth Tables ===\n\n");

	//NOT
	int r0 = not(0);
	int r1 = not(1);
	printf("NOT: 0->%d  1->%d  [%s]\n\n", r0, r1,
	(r0==1 && r1==0) ? "PASS" : "FAIL");
	{
	//AND
	int res[4];
	res[0] = and(0, 0);
	res[1] = and(0, 1);
	res[2] = and(1, 0);
	res[3] = and(1, 1);
	int exp[4] = {0,0,0,1};
	printf("AND: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}{
	//OR
	int res[4];
	res[0] = or(0, 0);
	res[1] = or(0, 1);
	res[2] = or(1, 0);
	res[3] = or(1, 1);
	int exp[4] = {0,1,1,1};
	printf("OR: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}{
	//XOR
	int res[4];
	res[0] = xor(0, 0);
	res[1] = xor(0, 1);
	res[2] = xor(1, 0);
	res[3] = xor(1, 1);
	int exp[4] = {0,1,1,0};
	printf("XOR: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}{
	//NAND
	int res[4];
	res[0] = nand(0, 0);
	res[1] = nand(0, 1);
	res[2] = nand(1, 0);
	res[3] = nand(1, 1);
	int exp[4] = {1,1,1,0};
	printf("NAND: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}{
	//NOR
	int res[4];
	res[0] = nor(0, 0);
	res[1] = nor(0, 1);
	res[2] = nor(1, 0);
	res[3] = nor(1, 1);
	int exp[4] = {1,0,0,0};
	printf("NOR: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}{
	//XNOR
	int res[4];
	res[0] = xnor(0, 0);
	res[1] = xnor(0, 1);
	res[2] = xnor(1, 0);
	res[3] = xnor(1, 1);
	int exp[4] = {1,0,0,1};
	printf("XNOR: 00->%d  01->%d  10->%d  11->%d  [%s]\n\n", res[0], res[1], res[2], res[3], 
	(res[0]==exp[0] && res[1]==exp[1] && res[2]==exp[2] && res[3]==exp[3]) ? "PASS" : "FAIL");
	}

	//Pt2 test CORRECT
	/*
	int S1, C1, S2, S2;
	half_adder(0, 1, &S1, &C1);
	printf("HA: %d%d", C1, S1);
	full_adder(0, 1, 0, &S2, &C2);
	printf("FA: %d%d", C2, S2);
	*/

	//Pt3 test CORRECT

	printf("\n=== Pt 2: Ripple Carry Adder ===\n");
	printf("Testing all 256 input combinations...\n");
	
	int passct = 0;
	int overflow;
	int expOverflow;
	uint8_t res;
	uint8_t exp;

	for(uint8_t a=0; a<16; a++){
		for(uint8_t b=0; b<16; b++){
			exp = bitwise_and((a+b),0b1111); 
			expOverflow = (a+b) >> 4;
			res = ripple_add(a, b, &overflow);
			if((res == exp) && (overflow == expOverflow))
				passct++;
			else{
				printf("FAIL: %d%d%d%d + ", and((a>>3), 1), and((a>>2), 1), and((a>>1), 1), and((a>>0), 1));
				printf("%d%d%d%d = ", and((b>>3), 1), and((b>>2), 1), and((b>>1), 1), and((b>>0), 1));
				printf("%d%d%d%d%d\n", overflow, and((res>>3), 1), and((res>>2), 1), and((res>>1), 1), and((res>>0), 1));
				printf("Expected: %d%d\n", expOverflow, exp);
			}
		}
	}
	printf("[%s] %d/256 Correct\n\n", (passct == 256) ? "PASS" : "FAIL", passct);
	

	//Pt 3 MUX

	printf("\n=== Pt 3: Multiplexer ===\n");
	printf("Testing 8 input combinations...\n");

	passct = 0;

	for(int s=0; s<=1; s++){
		for(int a=0; a<=1; a++){
			for(int b=0; b<=1; b++){
				exp = s ? b : a;
				res = mux(s, a, b);
				if(res == exp)	passct++;
				else{
					printf("FAIL: Sel,A,B %d%d%d->%d  ", s, a, b, res);
					printf("Expected: %d\n", exp);
				}
			}
		}
	}
	printf("[%s] %d/8 Correct\n\n", (passct == 8) ? "PASS" : "FAIL", passct);
	passct = 0;



	//Pt 4 ALU test CORRECT
	printf("=== Part 4: ALU ===\n");
	printf("Testing all ALU combinations...\n");


	//ADD
	for(uint8_t a=0; a<16; a++){
		for(uint8_t b=0; b<16; b++){
			exp = bitwise_and((a+b),0b1111); 
			res = alu(a, b, 0, 0);
			if(res == exp)
				passct++;
			else{
				printf("FAIL: %d%d%d%d + ", and((a>>3), 1), and((a>>2), 1), and((a>>1), 1), and((a>>0), 1));
				printf("%d%d%d%d = ", and((b>>3), 1), and((b>>2), 1), and((b>>1), 1), and((b>>0), 1));
				printf("%d%d%d%d\n", and((res>>3), 1), and((res>>2), 1), and((res>>1), 1), and((res>>0), 1));
				printf("Expected: %d\n", exp);
			}
		}
	}
	printf("ADD: [%s] %d/256 Correct\n", (passct == 256) ? "PASS" : "FAIL", passct);
	passct = 0;


	//AND
	for(uint8_t a=0; a<16; a++){
		for(uint8_t b=0; b<16; b++){
			exp = bitwise_and(a, b); 
			res = alu(a, b, 0, 1);
			if(res == exp)
				passct++;
			else{
				printf("FAIL: %d%d%d%d + ", and((a>>3), 1), and((a>>2), 1), and((a>>1), 1), and((a>>0), 1));
				printf("%d%d%d%d = ", and((b>>3), 1), and((b>>2), 1), and((b>>1), 1), and((b>>0), 1));
				printf("%d%d%d%d\n", and((res>>3), 1), and((res>>2), 1), and((res>>1), 1), and((res>>0), 1));
				printf("Expected: %d\n", exp);
			}
		}
	}
	printf("AND: [%s] %d/256 Correct\n", (passct == 256) ? "PASS" : "FAIL", passct);
	passct = 0;


	//OR
	for(uint8_t a=0; a<16; a++){
		for(uint8_t b=0; b<16; b++){
			exp = bitwise_or(a, b); 
			res = alu(a, b, 1, 0);
			if(res == exp)
				passct++;
			else{
				printf("FAIL: %d%d%d%d + ", and((a>>3), 1), and((a>>2), 1), and((a>>1), 1), and((a>>0), 1));
				printf("%d%d%d%d = ", and((b>>3), 1), and((b>>2), 1), and((b>>1), 1), and((b>>0), 1));
				printf("%d%d%d%d\n", and((res>>3), 1), and((res>>2), 1), and((res>>1), 1), and((res>>0), 1));
				printf("Expected: %d\n", exp);
			}
		}
	}
	printf("OR:  [%s] %d/256 Correct\n", (passct == 256) ? "PASS" : "FAIL", passct);
	passct = 0;


	//XOR
	for(uint8_t a=0; a<16; a++){
		for(uint8_t b=0; b<16; b++){
			exp = bitwise_xor(a, b); 
			res = alu(a, b, 1, 1);
			if(res == exp)
				passct++;
			else{
				printf("FAIL: %d%d%d%d + ", and((a>>3), 1), and((a>>2), 1), and((a>>1), 1), and((a>>0), 1));
				printf("%d%d%d%d = ", and((b>>3), 1), and((b>>2), 1), and((b>>1), 1), and((b>>0), 1));
				printf("%d%d%d%d\n", and((res>>3), 1), and((res>>2), 1), and((res>>1), 1), and((res>>0), 1));
				printf("Expected: %d\n", exp);
			}
		}
	}
	printf("XOR: [%s] %d/256 Correct\n", (passct == 256) ? "PASS" : "FAIL", passct);

    

    return 0;
}

/*
Reflection:

The hard part for me was definitely hitting the wall when testing the ripple adder
without bitwise functions. I thought I was really stuck but you led me the right way after
a lot of useless testing. I also later ran into trouble when using the mux in the ALU with
testing becuase I didn't realize i needed to build a bitwise mux as well. But, I'm super glad with how
everything turned out for this homework after all the hiccups along the way.

The MUX uses a series of gates to return one of two inputs base on a selector value. This avoids the need
for any selection structure like if/else. The control unit in the CPU also uses the same idea to choose
between different instructions. 

There would have to be a way for the numbers to add in parallel without having to rely on the time 
dealy from the carry over bits. A tradeoff would have to be some other layer of complexity like
increased numbers of gates and channels / physical size to impove the speed of the output.
*/