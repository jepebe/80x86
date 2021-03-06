#pragma once

#include <stdbool.h>
#include "80x86.h"

typedef struct {
    union {
        u8 opcode;
        struct {
            u8 reg_mem: 3;
            u8 reg_sreg: 3;
            u8 mode: 2;
        };
    };
} AddrMode;

typedef enum {
    BYTE,
    WORD
} OperandSize;

typedef enum {
    DEFAULT_SEGMENT,
    CS_SEGMENT,
    DS_SEGMENT,
    ES_SEGMENT,
    SS_SEGMENT
} SegmentOverride;

typedef enum {
    NO_REPEAT,
    REP,
    REPZ,
    REPNZ
} Repeat;

typedef union {
    u16 word; // status register
    struct {
        u8 CF: 1; // Carry Flag
        u8  : 1; // Not Used
        u8 PF: 1; // Parity Flag
        u8  : 1; // Not Used
        u8 AF: 1; // Auxiliary Carry Flag
        u8  : 1; // Not Used
        u8 ZF: 1; // Zero Flag
        u8 SF: 1; // Sign Flag
        u8 TF: 1; // Trap Flag
        u8 IF: 1; // Interrupt Flag
        u8 DF: 1; // Direction Flag
        u8 OF: 1; // Overflow Flag
        u8  : 4; // Not used
    };
} Flags;

typedef struct {
    union {
        u16 *word;
        u8 *byte;
    };
    union {
        u32 dword_cache;
        u16 word_cache;
        u8 byte_cache;
    };
    s16 displacement;
} Operand;

typedef struct {
    // Main registers
    union {
        u16 AX; // primary accumulator
        struct {
            u8 AL;  // ax low byte
            u8 AH;  // ax high byte
        };
    };

    union {
        u16 BX; // base, accumulator
        struct {
            u8 BL; // bx low byte
            u8 BH; // bx high byte
        };
    };

    union {
        u16 CX; // counter, accumulator
        struct {
            u8 CL; // cx low byte
            u8 CH; // cx high byte
        };
    };

    union {
        u16 DX; // accumulator, extended accumulator
        struct {
            u8 DL;  // dx low byte
            u8 DH;  // dx high byte
        };
    };

    // Index registers

    u16 SI; // source index
    u16 DI; // destination index
    u16 BP; // base pointer
    u16 SP; // stack pointer

    // program counter

    u16 IP; // instruction pointer

    // segment registers

    u16 CS; // code segment
    u16 DS; // data segment
    u16 ES; // extra segment
    u16 SS; // stack segment

    // status register
    Flags flags;

    u8 opcode;
    u16 opcode_ip;

    AddrMode addr_mode;
    bool halted;

    Operand read_op;
    Operand write_op;

    SegmentOverride segment_override;
    Repeat repeat;

    u64 instruction_count;
} CPU;



void cpu_reset(CPU *cpu);

/// Correctly return the IP in the CS segment
u32 cpu_ip(CPU *cpu);

/// Returns the SP location as an address in the SS segment
u32 cpu_sp(CPU *cpu);
