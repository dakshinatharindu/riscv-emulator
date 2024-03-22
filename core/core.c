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

    for (int i = 0; i < 252; i++) {
        printf("%02x", image[i]);
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
}

