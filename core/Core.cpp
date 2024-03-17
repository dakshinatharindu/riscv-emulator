//
// Created by Dakshina Tharindu on 3/10/24.
//

// Opcodes
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

#include "Core.h"
#include <iostream>

// Constructor
Core::Core() {
    this->pc = 0;
    for (int i = 0; i < 32; i++) {
        this->reg[i] = 0;
    }
    this->mem = new uint8_t[1024];
}

// Destructor
Core::~Core() = default;

// Run the core
void Core::run(int instrt) {
    switch (instrt & 0x7F) {
        case LUI: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                this->reg[rd] = imm;
            this->pc += 4;
            break;
        }
        case AUIPC: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                this->reg[rd] = this->pc + imm;
            this->pc += 4;
            break;
        }
        case JAL: {
            uint32_t imm = (instrt & 0x80000000) >> 11 | (instrt & 0x7FE00000) >> 20 |
                           (instrt & 0x100000) >> 9 | (instrt & 0xFF000);
            if (imm & 0x80000)
                imm |= 0xFFF00000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                this->reg[rd] = this->pc + 4;
            this->pc += imm;
            break;
        }
        case JALR: {
            uint32_t imm = (instrt & 0xFFF00000) >> 20;
            if (imm & 0x800)
                imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                this->reg[rd] = this->pc + 4;
            this->pc = (this->reg[rs1] + imm) & 0xFFFFFFFE;
            break;
        }
        case BRANCH: {
            uint32_t imm = (instrt & 0x80000000) >> 19 | (instrt & 0x7E000000) >> 20 |
                           (instrt & 0xF00) >> 7 | (instrt & 0x80) << 4;
            if (imm & 0x800)
                imm |= 0xFFFFF000;
            int32_t rs1_val = this->reg[(instrt >> 15) & 0x1F];
            int32_t rs2_val = this->reg[(instrt >> 20) & 0x1F];
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // BEQ
                    if (rs1_val == rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                case 0b001: // BNE
                    if (rs1_val != rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                case 0b100: // BLT
                    if (rs1_val < rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                case 0b101: // BGE
                    if (rs1_val >= rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                case 0b110: // BLTU
                    if ((uint32_t) rs1_val < (uint32_t) rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                case 0b111: // BGEU
                    if ((uint32_t) rs1_val >= (uint32_t) rs2_val)
                        this->pc += imm;
                    else
                        this->pc += 4;
                    break;
                default:
                    std::cout << "Unknown branch opcode" << std::endl;
            }
            break;
        }
        case LOAD: {
            uint32_t imm = instrt >> 20;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t addr = this->reg[rs1] + imm;
            uint32_t load_val = 0;
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // LB
                    load_val = *((int8_t *) (this->mem + addr));
                    break;
                case 0b001: // LH
                    load_val = *((int16_t *) (this->mem + addr));
                    break;
                case 0b010: // LW
                    load_val = *((uint32_t *) (this->mem + addr));
                    break;
                case 0b100: // LBU
                    load_val = *((uint8_t *) (this->mem + addr));
                    break;
                case 0b101: // LHU
                    load_val = *((uint16_t *) (this->mem + addr));
                    break;
                default:
                    std::cout << "Unknown load opcode" << std::endl;
            }
            if (rd) this->reg[rd] = load_val;
            this->pc += 4;
            break;
        }
        case STORE: {
            uint32_t imm = ((instrt >> 25) & 0x7F) << 5 | (instrt >> 7) & 0x1F;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rs2 = (instrt >> 20) & 0x1F;
            uint32_t addr = this->reg[rs1] + imm;
            uint32_t store_val = this->reg[rs2];
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // SB
                    *((uint8_t *) (this->mem + addr)) = store_val;
                    break;
                case 0b001: // SH
                    *((uint16_t *) (this->mem + addr)) = store_val;
                    break;
                case 0b010: // SW
                    *((uint32_t *) (this->mem + addr)) = store_val;
                    break;
                default:
                    std::cout << "Unknown store opcode" << std::endl;
            }
            this->pc += 4;
            break;
        }
        case OP_IMM: {
            uint32_t imm = instrt >> 20;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1_val = this->reg[(instrt >> 15) & 0x1F];
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t val = 0;
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // ADDI
                    val = rs1_val + imm;
                    break;
                case 0b010: // SLTI
                    val = (int32_t) rs1_val < (int32_t) imm;
                    break;
                case 0b011: // SLTIU
                    val = rs1_val < imm;
                    break;
                case 0b100: // XORI
                    val = rs1_val ^ imm;
                    break;
                case 0b110: // ORI
                    val = rs1_val | imm;
                    break;
                case 0b111: // ANDI
                    val = rs1_val & imm;
                    break;
                case 0b001: // SLLI
                    val = rs1_val << (imm & 0x1F);
                    break;
                case 0b101: // SRLI/SRAI
                    val = (instrt >> 30) ? (((int32_t) rs1_val) >> (imm & 0x1F)) : (rs1_val >> (imm & 0x1F));
                    break;
                default:
                    std::cout << "Unknown OP_IMM opcode" << std::endl;
            }
            if (rd) this->reg[rd] = val;
            this->pc += 4;
            break;
        }
        case OP: {
            uint32_t rs1_val = this->reg[(instrt >> 15) & 0x1F];
            uint32_t rs2_val = this->reg[(instrt >> 20) & 0x1F];
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t val = 0;
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // ADD/SUB
                    val = (instrt >> 30) ? (rs1_val - rs2_val) : (rs1_val + rs2_val);
                    break;
                case 0b001: // SLL
                    val = rs1_val << (rs2_val & 0x1F);
                    break;
                case 0b010: // SLT
                    val = (int32_t) rs1_val < (int32_t) rs2_val;
                    break;
                case 0b011: // SLTU
                    val = rs1_val < rs2_val;
                    break;
                case 0b100: // XOR
                    val = rs1_val ^ rs2_val;
                    break;
                case 0b101: // SRL/SRA
                    val = (instrt >> 30) ? (((int32_t) rs1_val) >> (rs2_val & 0x1F)) : (rs1_val >> (rs2_val & 0x1F));
                    break;
                case 0b110: // OR
                    val = rs1_val | rs2_val;
                    break;
                case 0b111: // AND
                    val = rs1_val & rs2_val;
                    break;
                default:
                    std::cout << "Unknown OP opcode" << std::endl;
            }
            if (rd) this->reg[rd] = val;
            this->pc += 4;
            break;
        }
        case FENCE: {
            this->pc += 4;
            break;
        }
        case SYSTEM: {
            this->pc += 4;
            break;
        }
        default:
            std::cout << "Unknown opcode" << std::endl;
    }
}

// Print the state of the core
void Core::print_state() {
    std::cout << "PC: " << (int32_t) this->pc << std::endl;
    for (int i = 0; i < 32; i++) {
        std::cout << "x" << i << ": " << (int32_t) this->reg[i] << std::endl;
    }
}
