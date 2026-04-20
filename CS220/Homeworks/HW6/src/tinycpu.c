#define RGFW_IMPLEMENTATION
#include "tinycpu.h"

// tinyCPU Startup Function
// Set all memory of the cpu struct to 0 
void cpu_init(tinyCPU* cpu) {
	memset(cpu, 0, sizeof(*cpu));
}

// Load the program into the tinyCPU memory starting at memory address 0
void cpu_load(tinyCPU* cpu, uint8_t* prog, size_t len) {
	for(int i=0; i<len; i++)
		cpu->mem[i] = prog[i];
}

// tinyCPU Fetch Step
// Use the program counter to get the current instruction and load each part into its byte array
// Increment the counter by the instruction length
// ============== YOU DO THIS ==============
void cpu_fetch(tinyCPU* cpu) {
	cpu->ir[0] = cpu->mem[cpu->pc];
	cpu->ir[1] = cpu->mem[cpu->pc+1];
	cpu->ir[2] = cpu->mem[cpu->pc+2];
	cpu->pc = 	 cpu->pc+3;
}

// tinyCPU "ALU" function
// Takes the place of an ALU make at the circuit level
uint8_t alu_compute(Op op, uint8_t a, uint8_t b)
{
	switch(op){
		case ADD:
			return a + b;
		case SUB:
			return a - b;
		case AND:
			return a & b;
		case OR:
			return a | b;
		case XOR:
			return a ^ b;
		case NOT:
			return ~a;
		case LSL:
			return a << (b & 7);
		case LSR:
			return a >> (b & 7);
	}
}

// tinyCPU Decode-Execute Step
// Since we are not bit packing the values into binary numbers, the decode step
// is just setting op, a, and b to the proper instrucion register
// Once again, since we are not on a circuit board decoding the opcode boils
// down into being a switch case for each instruction
// YOU implment each operations execution and the minimal decoding
// ============== YOU DO THIS ==============
void cpu_decode_execute(tinyCPU *cpu) {

	switch(cpu->ir[0]){
		case LDI:
			cpu->reg[cpu->ir[1]] = cpu->ir[2];
			break;
		case MOV:
			cpu->reg[cpu->ir[1]] = cpu->reg[cpu->ir[2]];
			break;
		case LD:
			cpu->reg[cpu->ir[1]] = cpu->mem[cpu->reg[cpu->ir[2]]];
			break;
		case ST:
			cpu->mem[cpu->reg[cpu->ir[1]]] = cpu->reg[cpu->ir[2]];
			break;	
		case ADD:
			cpu->reg[cpu->ir[1]] = alu_compute(ADD, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case SUB:
			cpu->reg[cpu->ir[1]] = alu_compute(SUB, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case AND:
			cpu->reg[cpu->ir[1]] = alu_compute(AND, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case OR:
			cpu->reg[cpu->ir[1]] = alu_compute(OR, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case XOR:
			cpu->reg[cpu->ir[1]] = alu_compute(XOR, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case NOT:
			cpu->reg[cpu->ir[1]] = alu_compute(NOT, cpu->reg[cpu->ir[1]], 0);
			break;
		case LSL:
			cpu->reg[cpu->ir[1]] = alu_compute(LSL, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case LSR:
			cpu->reg[cpu->ir[1]] = alu_compute(LSR, cpu->reg[cpu->ir[1]], cpu->reg[cpu->ir[2]]);
			break;
		case JMP:
			cpu->pc = cpu->ir[1]*3;
			break;
		case JMPI:
			cpu->pc = cpu->reg[cpu->ir[1]]*3;
			break;
		case JNZ:
			if(cpu->reg[cpu->ir[1]] !=0 )
			cpu->pc = cpu->ir[2]*3;
			break;
		case JZ:
			if(cpu->reg[cpu->ir[1]] == 0)
			cpu->pc = cpu->ir[2]*3;
			break;
		case HALT:
			cpu->halted = 1;
			break;
		case DRAW:{
			uint8_t x = cpu->reg[cpu->ir[1]];
			uint8_t y = cpu->reg[cpu->ir[2]];
			if (x < W && y < H)
				cpu->screen[y][x] = 1;
			cpu->needs_render = 1;
			break;}
		case DRAWOFF:{
			uint8_t x = cpu->reg[cpu->ir[1]];
			uint8_t y = cpu->reg[cpu->ir[2]];
			if (x < W && y < H)
				cpu->screen[y][x] = 0;
			cpu->needs_render = 1;
			break;}
		case CLEAR:
			switch(cpu->ir[1]){
				case 0:
					memset(cpu->screen, 0, sizeof(cpu->screen));
					break;
				case 1:
					memset(cpu->screen, 1, sizeof(cpu->screen));
					break;
			}
			cpu->needs_render = 1;
			break;

	}
}

// RENDER FUNCTIONS DO NOT TOUCH
// READ AT YOUR PLEASURE

void cpu_render_rgfw(tinyCPU* cpu, RGFW_window* win, RGFW_surface* surface) {
	u8* buf = surface->data;
	int scale = 8;

	memset(buf, 0, W * scale * H * scale * 4);

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (!cpu->screen[y][x]) continue;
				for (int py = 0; py < scale; py++) {
					for (int px = 0; px < scale; px++) {
						int bx = x * scale + px;
						int by = y * scale + py;
						int idx = (by * W * scale + bx) * 4;
						buf[idx + 0] = 255;
						buf[idx + 1] = 255;
						buf[idx + 2] = 255;
						buf[idx + 3] = 255;
					}
				}
			}
		}

		RGFW_window_blitSurface(win, surface);
}

void cpu_run(tinyCPU* cpu, int frame_delay_ms) {
	// Graphics stuff
	// Creating the window
	RGFW_window* win = RGFW_createWindow("tinyCPU", 0, 0, W*8, H*8, RGFW_windowCenter);
	u8* buffer = malloc(W*8 * H*8 * 4);
	RGFW_surface* surface = RGFW_createSurface(buffer, W*8, H*8, RGFW_formatRGBA8);
	if (!surface) {
		printf("Error: RGFW surface creation failed\n");
		return;
	}
	RGFW_event event;

	// Check if current program has thrown a HALT opcode
	// and that the PC doesn't go out of bounds
	while (!cpu->halted && cpu->pc <= MEM_SIZE - 3) {

		// Check if user closed graphics window
		while (RGFW_window_checkEvent(win, &event)) {
			if (event.type == RGFW_windowClose) goto done;
		}
		// Anytime a program updates the framebuffer we render it
		// other opcodes do not update it
		cpu->needs_render = 0;

		// Call Fetch on the CPU to load the next instruction into the
		// instruction register
		cpu_fetch(cpu);
		// Decode the instruction and execute its operation
		cpu_decode_execute(cpu);

		// Check if we need to render the screen
		if (cpu->needs_render) {
			cpu_render_rgfw(cpu, win, surface);
			sleep(frame_delay_ms);
		}
	}

	// CPU finished - keep window open until user closes it
	cpu_render_rgfw(cpu, win, surface);
	while (1) {
		RGFW_event event;
		RGFW_window_checkEvent(win, &event);
		if (RGFW_window_shouldClose(win)) break;
		sleep(frame_delay_ms);
	}

	done:
		RGFW_surface_free(surface);
		RGFW_window_close(win);
}