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

    state = (void *) image;
    printf("PC: %08x\n", state->pc);
    uint32_t instr = *(uint32_t *) (image + state->pc);
    printf("Instr: %08x\n", instr);

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
}

void execute() {
    if (state->pc & 3) {
        fprintf(stderr, "Error: PC is not word aligned\n");
        exit(EXIT_FAILURE);
    }

    uint32_t instr = *(uint32_t *) (image + state->pc);
}

