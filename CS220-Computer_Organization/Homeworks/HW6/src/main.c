#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "tinycpu.h"

int assemble(const char* prog_file, uint8_t* out_bytes);

int main(int argc, char const *argv[])
{
	// Check to make sure user properly uses the command
	// For example:
	// tinyCPU progs/sprite_moving.tiny 1
	// To run the sprite moving program with 1 milisecond delay between render frames 
	if (argc < 2) {
		printf("Error: Usage tinyCPU path/to/program.tiny frame_delay=10ms\n");
		return 1;
	}

	// Sets the frame delay for the 2nd command line argument
	int delay = 10;  // default 10ms
	if (argc >= 3) {
	    delay = atoi(argv[2]);
	}

	// Loads the 1st command line argment as a filename to be given to the assembler
	// This is how we translate .tiny code into tinyCPU machine code
	uint8_t prog[MEM_SIZE] = {0};
	int len = assemble(argv[1], prog);
	if (len < 0) {
		printf("Error: Assembler could not parse path/to/program.tiny\n");
		return 2;
	}

	printf("Info: Loaded %d bytes from %s...\n", len, argv[1]);

	printf("Info: Starting tinyCPU emulator...\n");

	tinyCPU cpu;

	cpu_init(&cpu);


	printf("Info: Loading program: %s into tinyCPU emulator...\n", argv[1]);

	cpu_load(&cpu, prog, len);

	printf("Info: Begining program: %s...\n", argv[1]);

	cpu_run(&cpu, delay);
	
	return 0;
}

// Maps mnemonic string to opcode number
// Returns -1 if not found
int mnemonic_to_opcode(const char *mnemonic) {
	const struct { const char *name; int opcode; } table[] = {
		{"LDI",     0}, {"MOV",     1}, {"LD",      2}, {"ST",      3},
		{"ADD",     4}, {"SUB",     5}, {"AND",     6}, {"OR",      7},
		{"XOR",     8}, {"NOT",     9}, {"LSL",    10}, {"LSR",    11},
		{"JMP",    12}, {"JMPI",   13}, {"JNZ",    14}, {"JZ",     15},
		{"HALT",   16}, {"DRAW",   17}, {"DRAWOFF",18}, {"CLEAR",  19},
	};
	for (int i = 0; i < 20; i++) {
		if (strcmp(mnemonic, table[i].name) == 0)
			return table[i].opcode;
	}
	return -1;
}

// Reads a .tiny file and fills out_bytes with the resulting program
// Returns the number of bytes written, or -1 on error
// out_bytes must be at least 256 bytes
/*
 * ==Writing tinyCPU Assembly Code==
 * Each line is composed of either, mnemonic instructions and operands
 * in the form of:
 * INSTRUCTION OPERAND_A OPERAND_B
 * or comments, denoted starting with a ; and ending with the next newline
 * EXAMPLE:
 * prog.tiny
 * LDI 0 255 ; loads R0 with 255
 * LDI 1 1   ; loads R1 with 1
 * ADD 0 1   ; R0 = R0 + R1 = 255 + 1 = 0 Overflow
 * HALT	     ; ends program
 */
int assemble(const char *filename, uint8_t *out_bytes) {

	// Opens a file in read mode
    FILE *f = fopen(filename, "r");
    if (!f) {
    	printf("Error: Could not open file: %s\n", filename);
    	return -1;
    }

    int byte_count = 0;
    char line[128];
    int line_num = 0;
    int in_data = 0;

    // Gets each line
    while (fgets(line, sizeof(line), f)) {
        line_num++;

        // Strip comments (everything after ';')
        char *comment = strchr(line, ';');
        if (comment) *comment = '\0';

        // Try to parse mnemonic and up to two operands
        char mnemonic[16];
        int a = 0, b = 0;
        int parsed = sscanf(line, "%15s %d %d", mnemonic, &a, &b);

        if (parsed <= 0) continue; // blank or comment-only line

	    // DATA sentinel - switch to raw byte mode
	    if (strcmp(mnemonic, "DATA") == 0) {
	        in_data = 1;
	        continue;
	    }

	    if (in_data) {
	        // DB just emits one raw byte
	        if (strcmp(mnemonic, "DB") == 0) {
	            if (byte_count >= MEM_SIZE) {
		        	printf("Error: in tinyCPU file '%s'\n", filename);
		            printf("\t[Line %d]: Program exceeds MEM_SIZE=%d\n", line_num, MEM_SIZE);
		            fclose(f);
		            return -1;
	            }
	            out_bytes[byte_count++] = (uint8_t)a;
	        }
	        continue; // skip opcode lookup entirely
	    }

        int opcode = mnemonic_to_opcode(mnemonic);

        if (opcode == -1) {
        	printf("Error: in tinyCPU file '%s'\n", filename);
            printf("\t[Line %d]: Unknown mnemonic '%s'\n", line_num, mnemonic);
            fclose(f);
            return -1;
        }

        if (byte_count + 3 > MEM_SIZE) {
        	printf("Error: in tinyCPU file '%s'\n", filename);
            printf("\t[Line %d]: Program exceeds MEM_SIZE=%d\n", line_num, MEM_SIZE);
            fclose(f);
            return -1;
        }

        out_bytes[byte_count++] = (uint8_t)opcode;
        out_bytes[byte_count++] = (uint8_t)a;
        out_bytes[byte_count++] = (uint8_t)b;
    }

    fclose(f);
    return byte_count;
}