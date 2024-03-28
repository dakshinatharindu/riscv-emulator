extern char uartbuffer[256];
extern char uarthead;
extern char uarttail;

void putuart(char c) {
    if (((unsigned char) (uarthead + 1)) == uarttail) return;
    uartbuffer[uarthead] = c;
    uarthead++;
}

void print(const char *str) {
    char c;
    while (c = *(str++)) putuart(c);
}

int main() {
    int a, b, c;
    a = 1;
    b = 2;
    c = a + b;
    print("Hello, World!\n");
}

int _start() {
    main();
    asm volatile("ebreak");
    return 0;
}
