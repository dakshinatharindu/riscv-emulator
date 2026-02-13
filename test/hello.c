// Simple bare-metal Hello World for RISC-V32 (QEMU virt machine)
// Prints directly to UART without any OS or firmware

#define UART_BASE 0x10000000
#define UART_THR  (UART_BASE + 0)  // Transmit Holding Register
#define UART_LSR  (UART_BASE + 5)  // Line Status Register
#define UART_LSR_THRE 0x20         // Transmitter Holding Register Empty

// void _start(void) __attribute__((section(".text.init")));

// Read from memory-mapped register
static inline unsigned char read_reg(unsigned long addr) {
    return *(volatile unsigned char *)addr;
}

// Write to memory-mapped register
static inline void write_reg(unsigned long addr, unsigned char val) {
    *(volatile unsigned char *)addr = val;
}

// Write a single byte to UART
void uart_putc(char c) {
    // Wait until transmitter is ready
    while ((read_reg(UART_LSR) & UART_LSR_THRE) == 0);
    
    // Send character
    write_reg(UART_THR, c);
}

// Write a string to UART
void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s);
        s++;
    }
}

// Entry point - this will be called by our startup code
void main(void) {
    uart_puts("Hello, RISC-V World!\n");
    uart_puts("Running in Machine mode (Priv: 3)\n");
    uart_puts("UART at 0x10000000\n");
    uart_puts("Success!\n");
    
    // Halt - infinite loop
    while (1) {
        __asm__ volatile ("wfi");  // Wait for interrupt
    }
}

// // Startup code - this is our actual entry point
// void _start(void) {
//     // Set up stack pointer (pointing to end of 1MB region)
//     __asm__ volatile (
//         "li sp, 0x80100000"
//         : : : "sp", "memory"  // Prevent reordering around memory operations
//     );
    
//     // Call main
//     main();
    
//     // Should never return, but just in case
//     while (1) {
//         __asm__ volatile ("wfi");
//     }
// }
