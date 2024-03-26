//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H

#define LUI     0b0110111
#define AUIPC   0b0010111
#define JAL     0b1101111
#define JALR    0b1100111
#define BRANCH  0b1100011
#define LOAD    0b0000011
#define STORE   0b0100011
#define OP_IMM  0b0010011
#define OP      0b0110011
#define FENCE   0b0001111
#define SYSTEM  0b1110011

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t *image;

struct State {
    uint32_t reg[32];
    uint32_t pc;
    uint32_t reserved[3];
} *state;

// Function prototypes
void load_image(char *filename);

void execute();

#endif // CORE_H
