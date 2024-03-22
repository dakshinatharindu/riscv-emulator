//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t *image;

struct State {
    uint32_t reg[32];
    uint32_t pc;
};

// Function prototypes
void load_image(char *filename);

#endif // CORE_H
