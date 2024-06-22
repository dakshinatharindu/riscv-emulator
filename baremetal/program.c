extern char uartbuffer[256];
extern char uarthead;
extern char uarttail;

void print(const char *str) {
    char c;
	uarttail = 0;
    while (c = *(str++)) {
		if (uarttail == 255) {
			asm volatile("ecall");
        }
		uartbuffer[uarttail] = c;
    	uarttail++;
	}
    asm volatile("ecall");
}

int main() {
    int a, b, c;
    a = 1;
    b = 2;
    c = a + b;
    print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur ornare leo sit amet ante molestie lacinia. Aliquam venenatis ut velit in cursus. Ut non porttitor quam. Maecenas vel feugiat nulla, in condimentum est. Fusce pharetra quam at metus aeadsf adsfa sdfk\n");
}

int _start() {
    main();
    asm volatile("ebreak");
    return 0;
}
