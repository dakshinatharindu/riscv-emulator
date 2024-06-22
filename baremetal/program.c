extern char uartbuffer[256];
extern char uarthead;
extern char uarttail;

void putuart(char c) {
    uartbuffer[uarttail] = c;
    uarttail++;
}

void print(const char *str) {
    char c;
    while (c = *(str++)) putuart(c);
    asm volatile("ecall");
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
