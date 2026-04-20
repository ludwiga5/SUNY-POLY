#pragma once

#include "RGFW.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define W 64
#define H 64
#define MEM_SIZE 256
#define REGS 16

typedef enum {
	LDI=0, MOV=1, LD=2, ST=3,
	ADD=4, SUB=5,
	AND=6, OR=7, XOR=8, NOT=9, LSL=10, LSR=11,
	JMP=12, JMPI=13, JNZ=14, JZ=15, HALT=16,
	DRAW=17, DRAWOFF=18, CLEAR=19
} Op;

typedef struct tinyCPU {
	uint8_t mem[MEM_SIZE];	//RAM memory bank
	uint8_t reg[REGS];  	//Register array
	uint8_t ir[3];			//Instruction register array
	uint8_t pc; 			//Program Counter

	bool halted;			//Halt flag
	bool needs_render; 		//Render flag

	uint8_t screen[H][W]; 	//2D Screen Buffer
} tinyCPU;

uint8_t alu_compute(Op op, uint8_t a, uint8_t b);
void cpu_draw_pixel(tinyCPU* cpu, uint8_t x, uint8_t y);
void cpu_render(tinyCPU* cpu);
void cpu_init(tinyCPU* cpu);
void cpu_load(tinyCPU* cpu, uint8_t* prog, size_t len);
void cpu_fetch(tinyCPU* cpu);
void cpu_decode_execute(tinyCPU* cpu);
void cpu_run(tinyCPU* cpu, int frame_delay_ms);