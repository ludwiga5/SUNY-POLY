#define RGFW_IMPLEMENTATION
#include "tinycpu.h"

// tinyCPU Startup Function
// Since its so simple you just set all memory of the cpu struct to 0 
// ============== YOU DO THIS ==============
void cpu_init(tinyCPU* cpu) {

}

// Load the program into the tinyCPU memory
// ============== YOU DO THIS ==============
void cpu_load(tinyCPU* cpu, uint8_t* prog, size_t len) {

}

// tinyCPU Fetch Step
// Use the PC to get the proper values and put them into the instruction register
// Dont forget to increment the PC!
// ============== YOU DO THIS ==============
void cpu_fetch(tinyCPU* cpu) {

}

// tinyCPU "ALU" function
// Takes the place of an ALU make at the circuit level
// You are allowed to use C's bitwise operators and arithmetic
// ============== YOU DO THIS ==============
uint8_t alu_compute(Op op, uint8_t a, uint8_t b)
{

}

// tinyCPU Decode-Execute Step
// Since we are not bit packing the values into binary numbers, the decode step
// is just setting op, a, and b to the proper instrucion register
// Once again, since we are not on a circuit board decoding the opcode boils
// down into being a switch case for each instruction
// YOU implment each operations execution and the minimal decoding
// ============== YOU DO THIS ==============
void cpu_decode_execute(tinyCPU *cpu) {

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
			Sleep(frame_delay_ms);
		}
	}

	// CPU finished - keep window open until user closes it
	cpu_render_rgfw(cpu, win, surface);
	while (1) {
		RGFW_event event;
		RGFW_window_checkEvent(win, &event);
		if (RGFW_window_shouldClose(win)) break;
		Sleep(frame_delay_ms);
	}

	done:
		RGFW_surface_free(surface);
		RGFW_window_close(win);
}