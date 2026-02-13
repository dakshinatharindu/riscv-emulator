.section .text.init
.globl _start

_start:
    # Set up stack pointer
    li sp, 0x80100000
    
    # Call main function
    call main
    
    # Infinite loop with wait-for-interrupt
1:
    wfi
    j 1b