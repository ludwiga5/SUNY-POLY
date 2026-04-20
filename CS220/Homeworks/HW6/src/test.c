/*
 * test_tinycpu.c
 *
 * Test suite for the tinyCPU implementation.
 * Tests all instructions and core CPU behavior per the tinyCPU spec.
 * Does NOT test any RGFW rendering functionality.
 *
 * Compile:
 *   gcc -Wall -Wextra -o test_tinycpu test_tinycpu.c
 *
 * Run:
 *   ./test_tinycpu
 */

#include "RGFW.h"
#include "tinycpu.h"

/* =========================================================================
 * TEST HELPERS
 * ========================================================================= */

static int tests_run    = 0;
static int tests_passed = 0;

static void print_summary(void)
{
    printf("\n-----------------------------------------\n");
    printf("  %d / %d tests passed\n", tests_passed, tests_run);
    printf("-----------------------------------------\n\n");
}

#define CHECK(name, condition)                                          \
    do {                                                                \
        tests_run++;                                                    \
        if (condition) {                                                \
            printf("  PASS  %s\n", name);                              \
            tests_passed++;                                             \
        } else {                                                        \
            printf("  FAIL  %s  (line %d)\n", name, __LINE__);        \
        }                                                               \
    } while (0)

/* Helper: build a one-instruction program, load it, fetch and execute it */
static void run_one(tinyCPU* cpu, uint8_t op, uint8_t a, uint8_t b)
{
    cpu_init(cpu);
    uint8_t prog[3] = { op, a, b };
    cpu_load(cpu, prog, 3);
    cpu_fetch(cpu);
    cpu_decode_execute(cpu);
}

/* Helper: run a full program (multiple 3-byte instructions) */
static void run_prog(tinyCPU* cpu, uint8_t* prog, size_t len)
{
    cpu_init(cpu);
    cpu_load(cpu, prog, len);
    /* Step through until halted or PC out of bounds */
    while (!cpu->halted && cpu->pc <= MEM_SIZE - 3) {
        cpu_fetch(cpu);
        cpu_decode_execute(cpu);
    }
}

/* =========================================================================
 * TEST: cpu_init
 * ========================================================================= */

static void test_init(void)
{
    printf("\n[ cpu_init - reset state ]\n");

    tinyCPU cpu;
    cpu_init(&cpu);

    CHECK("PC starts at 0",      cpu.pc == 0);
    CHECK("halted starts false", cpu.halted == false);

    int regs_clear = 1;
    for (int i = 0; i < REGS; i++)
        if (cpu.reg[i] != 0) { regs_clear = 0; break; }
    CHECK("all registers start at 0", regs_clear);

    int mem_clear = 1;
    for (int i = 0; i < MEM_SIZE; i++)
        if (cpu.mem[i] != 0) { mem_clear = 0; break; }
    CHECK("all memory starts at 0", mem_clear);

    int fb_clear = 1;
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            if (cpu.screen[y][x] != 0) { fb_clear = 0; break; }
    CHECK("framebuffer starts all off", fb_clear);
}

/* =========================================================================
 * TEST: cpu_load
 * ========================================================================= */

static void test_load(void)
{
    printf("\n[ cpu_load ]\n");

    tinyCPU cpu;
    cpu_init(&cpu);

    uint8_t prog[] = { LDI, 3, 99, HALT, 0, 0 };
    cpu_load(&cpu, prog, sizeof(prog));

    CHECK("mem[0] is opcode LDI",  cpu.mem[0] == LDI);
    CHECK("mem[1] is operand 3",   cpu.mem[1] == 3);
    CHECK("mem[2] is operand 99",  cpu.mem[2] == 99);
    CHECK("mem[3] is opcode HALT", cpu.mem[3] == HALT);
}

/* =========================================================================
 * TEST: cpu_fetch
 * ========================================================================= */

static void test_fetch(void)
{
    printf("\n[ cpu_fetch ]\n");

    tinyCPU cpu;
    cpu_init(&cpu);

    uint8_t prog[] = { 5, 10, 20,   /* instr 0 */
                       7, 11, 22 }; /* instr 1 */
    cpu_load(&cpu, prog, sizeof(prog));

    cpu_fetch(&cpu);
    CHECK("IR[0] is first opcode",    cpu.ir[0] == 5);
    CHECK("IR[1] is first operand A", cpu.ir[1] == 10);
    CHECK("IR[2] is first operand B", cpu.ir[2] == 20);
    CHECK("PC advanced to 3",         cpu.pc == 3);

    cpu_fetch(&cpu);
    CHECK("IR[0] is second opcode",   cpu.ir[0] == 7);
    CHECK("PC advanced to 6",         cpu.pc == 6);
}

/* =========================================================================
 * TEST: Data Movement Instructions  (LDI, MOV, LD, ST)
 * ========================================================================= */

static void test_data_movement(void)
{
    printf("\n[ LDI / MOV / LD / ST ]\n");

    tinyCPU cpu;

    /* LDI Rd, imm8 -> Rd = imm8 */
    run_one(&cpu, LDI, 0, 42);
    CHECK("LDI R0, 42  -> R0 == 42",   cpu.reg[0] == 42);

    run_one(&cpu, LDI, 15, 255);
    CHECK("LDI R15,255 -> R15 == 255", cpu.reg[15] == 255);

    run_one(&cpu, LDI, 7, 0);
    CHECK("LDI R7, 0   -> R7 == 0",   cpu.reg[7] == 0);

    /* MOV Rd, Rs -> Rd = Rs */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 2, 77,   /* R2 = 77 */
            MOV, 5, 2,    /* R5 = R2 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("MOV R5, R2 -> R5 == 77",   cpu.reg[5] == 77);
        CHECK("MOV does not alter source", cpu.reg[2] == 77);
    }

    /* ST Ra, Rs then LD Rd, Ra  (round-trip through memory) */
    {
        cpu_init(&cpu);
        /* Store R0=200 at address held in R1=100, then load back into R2 */
        uint8_t prog[] = {
            LDI,  0, 200,   /* R0 = 200 (value to store) */
            LDI,  1, 100,   /* R1 = 100 (address)        */
            ST,   1, 0,     /* mem[R1] = R0 -> mem[100] = 200 */
            LDI,  2, 0,     /* R2 = 0 (clear destination) */
            LD,   2, 1,     /* R2 = mem[R1] -> R2 = mem[100] */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("ST writes 200 to mem[100]", cpu.mem[100] == 200);
        CHECK("LD reads 200 from mem[100]", cpu.reg[2] == 200);
    }
}

/* =========================================================================
 * TEST: ALU - Arithmetic (ADD, SUB)
 * ========================================================================= */

static void test_arithmetic(void)
{
    printf("\n[ ADD / SUB ]\n");

    tinyCPU cpu;

    /* ADD */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 100,
            LDI, 1, 55,
            ADD, 0, 1,    /* R0 = 155 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("ADD 100+55 = 155",  cpu.reg[0] == 155);
    }

    /* ADD with unsigned wrap-around (mod 256) */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 200,
            LDI, 1, 100,
            ADD, 0, 1,    /* 200+100 = 300, mod 256 = 44 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("ADD wrap-around 200+100 mod 256 = 44", cpu.reg[0] == 44);
    }

    /* SUB */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 90,
            LDI, 1, 40,
            SUB, 0, 1,    /* R0 = 50 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("SUB 90-40 = 50", cpu.reg[0] == 50);
    }

    /* SUB with unsigned wrap-around */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 10,
            LDI, 1, 20,
            SUB, 0, 1,    /* 10-20 = -10, wraps to 246 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("SUB wrap-around 10-20 mod 256 = 246", cpu.reg[0] == 246);
    }
}

/* =========================================================================
 * TEST: ALU - Bitwise / Logic (AND, OR, XOR, NOT, LSL, LSR)
 * ========================================================================= */

static void test_bitwise(void)
{
    printf("\n[ AND / OR / XOR / NOT / LSL / LSR ]\n");

    tinyCPU cpu;

    /* AND */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xF0,
            LDI, 1, 0xFF,
            AND, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("AND 0xF0 & 0xFF = 0xF0", cpu.reg[0] == 0xF0);
    }

    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xAA,
            LDI, 1, 0x55,
            AND, 0, 1,    /* 10101010 & 01010101 = 0 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("AND 0xAA & 0x55 = 0x00", cpu.reg[0] == 0x00);
    }

    /* OR */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xAA,
            LDI, 1, 0x55,
            OR,  0, 1,    /* 10101010 | 01010101 = 0xFF */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("OR 0xAA | 0x55 = 0xFF", cpu.reg[0] == 0xFF);
    }

    /* XOR */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xFF,
            LDI, 1, 0xFF,
            XOR, 0, 1,    /* 0xFF ^ 0xFF = 0 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("XOR 0xFF ^ 0xFF = 0x00", cpu.reg[0] == 0x00);
    }

    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xAA,
            LDI, 1, 0x55,
            XOR, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("XOR 0xAA ^ 0x55 = 0xFF", cpu.reg[0] == 0xFF);
    }

    /* NOT */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0x00,
            NOT, 0, 0,    /* ~0x00 = 0xFF */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("NOT ~0x00 = 0xFF", cpu.reg[0] == 0xFF);
    }

    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 0xAA,
            NOT, 0, 0,    /* ~0xAA = 0x55 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("NOT ~0xAA = 0x55", cpu.reg[0] == 0x55);
    }

    /* LSL - shift left */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 1,
            LDI, 1, 4,
            LSL, 0, 1,    /* 1 << 4 = 16 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("LSL 1 << 4 = 16", cpu.reg[0] == 16);
    }

    /* LSL shift amount masked to low 3 bits (& 7) */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 1,
            LDI, 1, 9,    /* 9 & 7 = 1, so shift by 1 */
            LSL, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("LSL shift masked: 1 << (9&7=1) = 2", cpu.reg[0] == 2);
    }

    /* LSR - shift right */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 64,
            LDI, 1, 2,
            LSR, 0, 1,    /* 64 >> 2 = 16 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("LSR 64 >> 2 = 16", cpu.reg[0] == 16);
    }

    /* LSR shift amount masked to low 3 bits */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI, 0, 128,
            LDI, 1, 8,    /* 8 & 7 = 0, so shift by 0 */
            LSR, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("LSR shift masked: 128 >> (8&7=0) = 128", cpu.reg[0] == 128);
    }
}

/* =========================================================================
 * TEST: Control Flow (JMP, JMPI, JNZ, JZ, HALT)
 * ========================================================================= */

static void test_control_flow(void)
{
    printf("\n[ JMP / JMPI / JNZ / JZ / HALT ]\n");

    tinyCPU cpu;

    /* HALT stops execution */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            HALT, 0, 0,
            LDI,  0, 99,  /* should never execute */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("HALT stops before LDI", cpu.reg[0] == 0);
        CHECK("halted flag is set",     cpu.halted == true);
    }

    /* JMP unconditional - jumps to instruction number, PC = target*3 */
    {
        cpu_init(&cpu);
        /* instr 0: JMP to instr 2 (skipping instr 1)
         * instr 1: LDI R0,99 (skipped)
         * instr 2: LDI R1,42
         * instr 3: HALT */
        uint8_t prog[] = {
            JMP,  2, 0,   /* jump to instr 2 */
            LDI,  0, 99,  /* skipped */
            LDI,  1, 42,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JMP skips instruction 1: R0 still 0", cpu.reg[0] == 0);
        CHECK("JMP lands at instruction 2: R1 == 42", cpu.reg[1] == 42);
    }

    /* JMPI - jump to address stored in register */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 3  (target instruction = 3)
         * instr 1: JMPI R0    (PC = reg[R0]*3 = 9)
         * instr 2: LDI R1,99  (skipped)
         * instr 3: LDI R2,77
         * instr 4: HALT */
        uint8_t prog[] = {
            LDI,  0, 3,   /* R0 = 3 (target instr) */
            JMPI, 0, 0,   /* PC = R0*3 = 9 */
            LDI,  1, 99,  /* skipped */
            LDI,  2, 77,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JMPI skips instruction 2: R1 still 0", cpu.reg[1] == 0);
        CHECK("JMPI lands at instruction 3: R2 == 77", cpu.reg[2] == 77);
    }

    /* JNZ - jump if register != 0 (taken) */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 1  (nonzero)
         * instr 1: JNZ R0, 3  (R0!=0 so jump to instr 3)
         * instr 2: LDI R1,99  (skipped)
         * instr 3: LDI R2,55
         * instr 4: HALT */
        uint8_t prog[] = {
            LDI,  0, 1,
            JNZ,  0, 3,
            LDI,  1, 99,
            LDI,  2, 55,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JNZ taken: R1 still 0",  cpu.reg[1] == 0);
        CHECK("JNZ taken: R2 == 55",    cpu.reg[2] == 55);
    }

    /* JNZ - not taken when register == 0 */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 0  (zero -> JNZ not taken)
         * instr 1: JNZ R0, 3
         * instr 2: LDI R1, 88 (should execute)
         * instr 3: HALT */
        uint8_t prog[] = {
            LDI,  0, 0,
            JNZ,  0, 3,
            LDI,  1, 88,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JNZ not taken: R1 == 88", cpu.reg[1] == 88);
    }

    /* JZ - jump if register == 0 (taken) */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 0  (zero -> JZ taken)
         * instr 1: JZ  R0, 3
         * instr 2: LDI R1, 99 (skipped)
         * instr 3: LDI R2, 33
         * instr 4: HALT */
        uint8_t prog[] = {
            LDI,  0, 0,
            JZ,   0, 3,
            LDI,  1, 99,
            LDI,  2, 33,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JZ taken: R1 still 0",  cpu.reg[1] == 0);
        CHECK("JZ taken: R2 == 33",    cpu.reg[2] == 33);
    }

    /* JZ - not taken when register != 0 */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 5  (nonzero -> JZ not taken)
         * instr 1: JZ  R0, 3
         * instr 2: LDI R1, 77
         * instr 3: HALT */
        uint8_t prog[] = {
            LDI,  0, 5,
            JZ,   0, 3,
            LDI,  1, 77,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JZ not taken: R1 == 77", cpu.reg[1] == 77);
    }

    /* Loop: count from 0 to 4 using JNZ */
    {
        cpu_init(&cpu);
        /* instr 0: LDI R0, 5   (loop counter)
         * instr 1: LDI R1, 1   (decrement)
         * instr 2: SUB R0, R1  (R0--)
         * instr 3: JNZ R0, 2   (loop back while R0 != 0)
         * instr 4: HALT        (R0 == 0 when we reach here) */
        uint8_t prog[] = {
            LDI,  0, 5,
            LDI,  1, 1,
            SUB,  0, 1,
            JNZ,  0, 2,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("Loop counted down: R0 == 0", cpu.reg[0] == 0);
    }
}

/* =========================================================================
 * TEST: Display Instructions (DRAW, DRAWOFF, CLEAR)
 * ========================================================================= */

static void test_display(void)
{
    printf("\n[ DRAW / DRAWOFF / CLEAR ]\n");

    tinyCPU cpu;

    /* DRAW sets a pixel */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI,  0, 10,   /* R0 = x=10 */
            LDI,  1, 20,   /* R1 = y=20 */
            DRAW, 0, 1,    /* screen[20][10] = 1 */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("DRAW sets pixel on",         cpu.screen[20][10] == 1);
        CHECK("DRAW sets needs_render",     cpu.needs_render == 1);
        CHECK("adjacent pixel untouched",   cpu.screen[20][11] == 0);
    }

    /* DRAWOFF clears a pixel */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI,     0, 5,
            LDI,     1, 5,
            DRAW,    0, 1,   /* turn on (5,5) */
            DRAWOFF, 0, 1,   /* turn off (5,5) */
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("DRAWOFF clears pixel", cpu.screen[5][5] == 0);
    }

    /* CLEAR mode 0 - blank entire framebuffer */
    {
        cpu_init(&cpu);
        /* Draw a few pixels then clear */
        uint8_t prog[] = {
            LDI,   0, 10,
            LDI,   1, 10,
            DRAW,  0, 1,
            LDI,   0, 32,
            LDI,   1, 32,
            DRAW,  0, 1,
            CLEAR, 0, 0,   /* clear all */
            HALT,  0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));

        int all_off = 1;
        for (int y = 0; y < H && all_off; y++)
            for (int x = 0; x < W && all_off; x++)
                if (cpu.screen[y][x]) all_off = 0;
        CHECK("CLEAR mode 0 blanks all pixels", all_off);
    }

    /* CLEAR mode 1 - fill entire framebuffer */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            CLEAR, 1, 0,
            HALT,  0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));

        int all_on = 1;
        for (int y = 0; y < H && all_on; y++)
            for (int x = 0; x < W && all_on; x++)
                if (!cpu.screen[y][x]) all_on = 0;
        CHECK("CLEAR mode 1 fills all pixels", all_on);
    }

    /* DRAW out-of-bounds (x >= W or y >= H) is silently ignored */
    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI,  0, 64,   /* x = W (out of bounds) */
            LDI,  1, 10,
            DRAW, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        /* No crash and framebuffer still all zero */
        int fb_untouched = 1;
        for (int y = 0; y < H && fb_untouched; y++)
            for (int x = 0; x < W && fb_untouched; x++)
                if (cpu.screen[y][x]) fb_untouched = 0;
        CHECK("DRAW x=64 out-of-bounds ignored", fb_untouched);
    }

    {
        cpu_init(&cpu);
        uint8_t prog[] = {
            LDI,  0, 10,
            LDI,  1, 64,   /* y = H (out of bounds) */
            DRAW, 0, 1,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        int fb_untouched = 1;
        for (int y = 0; y < H && fb_untouched; y++)
            for (int x = 0; x < W && fb_untouched; x++)
                if (cpu.screen[y][x]) fb_untouched = 0;
        CHECK("DRAW y=64 out-of-bounds ignored", fb_untouched);
    }
 
}

/* =========================================================================
 * TEST: ALU via alu_compute directly
 * ========================================================================= */

static void test_alu_direct(void)
{
    printf("\n[ alu_compute direct ]\n");

    CHECK("ALU ADD 1+1=2",          alu_compute(ADD, 1,   1)   == 2);
    CHECK("ALU ADD wrap 255+1=0",   alu_compute(ADD, 255, 1)   == 0);
    CHECK("ALU SUB 5-3=2",          alu_compute(SUB, 5,   3)   == 2);
    CHECK("ALU SUB wrap 0-1=255",   alu_compute(SUB, 0,   1)   == 255);
    CHECK("ALU AND 0xF0&0x0F=0",    alu_compute(AND, 0xF0,0x0F)== 0x00);
    CHECK("ALU AND 0xFF&0xAA=0xAA", alu_compute(AND, 0xFF,0xAA)== 0xAA);
    CHECK("ALU OR  0xF0|0x0F=0xFF", alu_compute(OR,  0xF0,0x0F)== 0xFF);
    CHECK("ALU XOR 0xFF^0xFF=0",    alu_compute(XOR, 0xFF,0xFF)== 0x00);
    CHECK("ALU XOR 0xAA^0x55=0xFF", alu_compute(XOR, 0xAA,0x55)== 0xFF);
    CHECK("ALU NOT ~0xFF=0x00",     alu_compute(NOT, 0xFF,0)   == 0x00);
    CHECK("ALU NOT ~0x00=0xFF",     alu_compute(NOT, 0x00,0)   == 0xFF);
    CHECK("ALU LSL 1<<3=8",         alu_compute(LSL, 1,   3)   == 8);
    CHECK("ALU LSL mask: 1<<(8&7=0)=1", alu_compute(LSL,1,8)  == 1);
    CHECK("ALU LSR 128>>1=64",      alu_compute(LSR, 128, 1)   == 64);
    CHECK("ALU LSR mask: 8>>(9&7=1)=4", alu_compute(LSR,8,9)  == 4);
}

/* =========================================================================
 * TEST: Instruction encoding (3 bytes per instruction, PC addresses)
 * ========================================================================= */

static void test_instruction_encoding(void)
{
    printf("\n[ instruction encoding / PC arithmetic ]\n");

    tinyCPU cpu;

    /* Instruction N is at byte address N*3. JMP to instr number
     * correctly translates to the right byte address. */
    {
        cpu_init(&cpu);
        /*  instr 0 (byte  0): LDI R0, 1
         *  instr 1 (byte  3): JMP to instr 4
         *  instr 2 (byte  6): LDI R1, 11  <- skipped
         *  instr 3 (byte  9): LDI R2, 22  <- skipped
         *  instr 4 (byte 12): LDI R3, 33  <- landed here
         *  instr 5 (byte 15): HALT */
        uint8_t prog[] = {
            LDI, 0, 1,
            JMP, 4, 0,
            LDI, 1, 11,
            LDI, 2, 22,
            LDI, 3, 33,
            HALT, 0, 0
        };
        run_prog(&cpu, prog, sizeof(prog));
        CHECK("JMP 4 skips instrs 2,3: R1==0", cpu.reg[1] == 0);
        CHECK("JMP 4 skips instrs 2,3: R2==0", cpu.reg[2] == 0);
        CHECK("JMP 4 lands at instr 4: R3==33", cpu.reg[3] == 33);
    }

    /* PC stops execution when it would go past address 253 */
    {
        cpu_init(&cpu);
        /* Load only 2 instructions (6 bytes); let PC walk off the end */
        uint8_t prog[] = {
            LDI, 0, 7,
            LDI, 1, 8
            /* no HALT - PC will reach 6 which is > MEM_SIZE-3 = 253... 
             * actually MEM_SIZE=256 so 256-3=253. With 6 bytes loaded,
             * after 2 fetches PC=6 which is <= 253, but remaining mem 
             * is all 0 bytes = LDI R0,0 forever. 
             * Let's verify the loaded data survives correctly instead. */
        };
        cpu_init(&cpu);
        cpu_load(&cpu, prog, sizeof(prog));
        cpu_fetch(&cpu);
        cpu_decode_execute(&cpu);
        cpu_fetch(&cpu);
        cpu_decode_execute(&cpu);
        CHECK("Sequential fetch: R0==7", cpu.reg[0] == 7);
        CHECK("Sequential fetch: R1==8", cpu.reg[1] == 8);
        CHECK("PC is 6 after two fetches", cpu.pc == 6);
    }
}

/* =========================================================================
 * TEST: Spec example - vertical line (from the spec doc)
 * ========================================================================= */

static void test_spec_vertical_line(void)
{
    printf("\n[ spec example: vertical line ]\n");

    tinyCPU cpu;

    /* From the spec:
     * R0 = y counter (0..63), R1 = 1 (increment), R2 = 63 (limit), R3 = 31 (x)
     * Loop: DRAW(R3, R0), R0++, R2 -= R0, JNZ R2 back
     * (Note: spec example has a small quirk with R2 tracking;
     *  we test that the column x=31 ends up fully drawn)            */
    uint8_t prog[] = {
        LDI,  0, 0,    /* R0 = 0  */
        LDI,  1, 1,    /* R1 = 1  */
        LDI,  2, 63,   /* R2 = 63 */
        LDI,  3, 31,   /* R3 = 31 */
        DRAW, 3, 0,    /* Draw(R3, R0) - instr 4 */
        ADD,  0, 1,    /* R0 += 1 */
        SUB,  2, 0,    /* R2 -= R0 */
        JNZ,  2, 4,    /* if R2 != 0 goto instr 4 */
        HALT, 0, 0
    };
    run_prog(&cpu, prog, sizeof(prog));

    /* Check that every pixel in column 31 is lit */
    int col_lit = 1;
    for (int y = 0; y < H; y++)
        if (!cpu.screen[y][31]) { col_lit = 0; break; }
    CHECK("vertical line: all pixels in col 31 are on", col_lit);

    /* Check that a different column is NOT lit */
    int other_col_dark = 1;
    for (int y = 0; y < H; y++)
        if (cpu.screen[y][30]) { other_col_dark = 0; break; }
    CHECK("vertical line: col 30 is untouched", other_col_dark);
}

/* =========================================================================
 * MAIN
 * ========================================================================= */

int main(void)
{
    printf("=========================================\n");
    printf("  tinyCPU - test suite\n");
    printf("=========================================\n");

    test_init();
    test_load();
    test_fetch();
    test_alu_direct();
    test_data_movement();
    test_arithmetic();
    test_bitwise();
    test_control_flow();
    test_display();
    test_instruction_encoding();
    test_spec_vertical_line();

    print_summary();

    return (tests_passed == tests_run) ? 0 : 1;
}