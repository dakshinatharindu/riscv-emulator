//
// Created by Dakshina Tharindu on 3/10/24.
//

#include "core.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    load_image(argv[1]);

    uint8_t ret;
    while (1) {
        ret = execute();
        if (ret) break;
    }

    return 0;
}

void load_image(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    long flen = ftell(f);
    fseek(f, 0, SEEK_SET);

    image = malloc(flen);
    if (fread(image, 1, flen, f) != flen) {
        fprintf(stderr, "Error: Could not read file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fclose(f);

    // Initialize the state
    state = (void *) image;
}

uint8_t execute() {
    if (state->pc & 3) {
        fprintf(stderr, "Error: PC is not word aligned\n");
        exit(EXIT_FAILURE);
    }

    uint32_t instrt = *(uint32_t *) (image + state->pc);

    uint8_t ret = 0;

    switch (instrt & 0x7F) {
        case LUI: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                state->reg[rd] = imm;
            state->pc += 4;
            break;
        }
        case AUIPC: {
            uint32_t imm = instrt & 0xFFFFF000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                state->reg[rd] = state->pc + imm;
            state->pc += 4;
            break;
        }
        case JAL: {
            uint32_t imm = (instrt & 0x80000000) >> 11 | (instrt & 0x7FE00000) >> 20 |
                           (instrt & 0x100000) >> 9 | (instrt & 0xFF000);
            if (imm & 0x80000)
                imm |= 0xFFF00000;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                state->reg[rd] = state->pc + 4;
            state->pc += imm;
            break;
        }
        case JALR: {
            uint32_t imm = (instrt & 0xFFF00000) >> 20;
            if (imm & 0x800)
                imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rd = (instrt >> 7) & 0x1F;
            if (rd)
                state->reg[rd] = state->pc + 4;
            state->pc = (state->reg[rs1] + imm) & 0xFFFFFFFE;
            break;
        }
        case BRANCH: {
            uint32_t imm = (instrt & 0x80000000) >> 19 | (instrt & 0x7E000000) >> 20 |
                           (instrt & 0xF00) >> 7 | (instrt & 0x80) << 4;
            if (imm & 0x800)
                imm |= 0xFFFFF000;
            int32_t rs1_val = (int32_t) state->reg[(instrt >> 15) & 0x1F];
            int32_t rs2_val = (int32_t) state->reg[(instrt >> 20) & 0x1F];
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // BEQ
                    if (rs1_val == rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                case 0b001: // BNE
                    if (rs1_val != rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                case 0b100: // BLT
                    if (rs1_val < rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                case 0b101: // BGE
                    if (rs1_val >= rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                case 0b110: // BLTU
                    if ((uint32_t) rs1_val < (uint32_t) rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                case 0b111: // BGEU
                    if ((uint32_t) rs1_val >= (uint32_t) rs2_val)
                        state->pc += imm;
                    else
                        state->pc += 4;
                    break;
                default:
                    fprintf(stderr, "Unknown branch opcode\n");
                    exit(EXIT_FAILURE);
            }
            break;
        }
        case LOAD: {
            uint32_t imm = instrt >> 20;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t addr = state->reg[rs1] + imm;
            uint32_t load_val = 0;
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // LB
                    load_val = *((int8_t *) (image + addr));
                    break;
                case 0b001: // LH
                    load_val = *((int16_t *) (image + addr));
                    break;
                case 0b010: // LW
                    load_val = *((uint32_t *) (image + addr));
                    break;
                case 0b100: // LBU
                    load_val = *((uint8_t *) (image + addr));
                    break;
                case 0b101: // LHU
                    load_val = *((uint16_t *) (image + addr));
                    break;
                default:
                    fprintf(stderr, "Unknown load opcode\n");
                    exit(EXIT_FAILURE);
            }
            if (rd) state->reg[rd] = load_val;
            state->pc += 4;
            break;
        }
        case STORE: {
            uint32_t imm = ((instrt >> 25) & 0x7F) << 5 | (instrt >> 7) & 0x1F;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1 = (instrt >> 15) & 0x1F;
            uint32_t rs2 = (instrt >> 20) & 0x1F;
            uint32_t addr = state->reg[rs1] + imm;
            uint32_t store_val = state->reg[rs2];
            switch ((instrt >> 12) & 0x7) {
                case 0b000: // SB
                    *((uint8_t *) (image + addr)) = store_val;
                    break;
                case 0b001: // SH
                    *((uint16_t *) (image + addr)) = store_val;
                    break;
                case 0b010: // SW
                    *((uint32_t *) (image + addr)) = store_val;
                    break;
                default:
                    fprintf(stderr, "Unknown store opcode\n");
                    exit(EXIT_FAILURE);
            }
            state->pc += 4;
            break;
        }
        case OP_IMM: {
            uint32_t imm = instrt >> 20;
            if (imm & 0x800) imm |= 0xFFFFF000;
            uint32_t rs1_val = state->reg[(instrt >> 15) & 0x1F];
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t val;
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
                    fprintf(stderr, "Unknown OP_IMM opcode\n");
                    exit(EXIT_FAILURE);
            }
            if (rd) state->reg[rd] = val;
            state->pc += 4;
            break;
        }
        case OP: {
            uint32_t rs1_val = state->reg[(instrt >> 15) & 0x1F];
            uint32_t rs2_val = state->reg[(instrt >> 20) & 0x1F];
            uint32_t rd = (instrt >> 7) & 0x1F;
            uint32_t val;
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
                    fprintf(stderr, "Unknown OP opcode\n");
                    exit(EXIT_FAILURE);
            }
            if (rd) state->reg[rd] = val;
            state->pc += 4;
            break;
        }
        case FENCE: {
            state->pc += 4;
            break;
        }
        case SYSTEM: {
            state->pc += 4;
            ret = 1;
            break;
        }
        default:
            fprintf(stderr, "Unknown opcode\n");
            exit(EXIT_FAILURE);
    }
}

