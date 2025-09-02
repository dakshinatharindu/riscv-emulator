//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LUI 0b0110111
#define AUIPC 0b0010111
#define JAL 0b1101111
#define JALR 0b1100111
#define BRANCH 0b1100011
#define LOAD 0b0000011
#define STORE 0b0100011
#define OP_IMM 0b0010011
#define OP 0b0110011
#define FENCE 0b0001111
#define SYSTEM 0b1110011

#define IMAGE_OFFSET 0x80000000

#define SET_CSR(csr, val) { state->csr = val; }
#define GET_CSR(csr) (state->csr)

uint8_t *image;
const static uint32_t MEM_SIZE = 1 << 24;

struct State {
  uint32_t reg[32]; // Register file
  uint32_t pc;      // Program counter

  uint32_t mstatus;
	uint32_t cycle;

	uint32_t mscratch;
	uint32_t mtvec;
	uint32_t mie;
	uint32_t mip;
  uint32_t misa; // RV32IM
  uint32_t mvendorid;

	uint32_t mepc;
	uint32_t mtval;
	uint32_t mcause;
} *state;

// Function prototypes
void load_image(char *filename);
uint8_t execute();
void print_handler(uint32_t ptr);

#endif // CORE_H
