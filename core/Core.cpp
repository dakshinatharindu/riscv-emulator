//
// Created by Dakshina Tharindu on 3/10/24.
//

// Opcodes
#define LUI     0b0110111
#define AUIPC   0b0010111

#include "Core.h"
#include <iostream>

// Constructor
Core::Core() {
    pc = 0;
    for (int i = 0; i < 32; i++) {
        reg[i] = 0;
    }
}

// Destructor
Core::~Core() {
    // Nothing to do here
}

// Run the core
void Core::run(int instrt) {
    switch (instrt & 0x7F) {
        case LUI: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd) this->reg[rd] = imm;
            this->pc += 4;
            break;
        }
        case AUIPC: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd) this->reg[rd] = this->pc + imm;
            this->pc += 4;
            break;
        }
        default:
            std::cout << "Unknown opcode" << std::endl;
    }
}

// Print the state of the core
void Core::print_state() {
    std::cout << "PC: " << this->pc << std::endl;
    for (int i = 0; i < 32; i++) {
        std::cout << "x" << i << ": " << this->reg[i] << std::endl;
    }
}

