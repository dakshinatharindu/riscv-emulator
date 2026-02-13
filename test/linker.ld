/* Linker script for RISC-V32 bare-metal program */
/* Designed for QEMU virt machine */

OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
    /* Start at beginning of RAM */
    . = 0x80000000;
    
    .text : {
        *(.text.init)    /* _start goes here FIRST */
        *(.text*)        /* Everything else after */
    }
    
    .rodata : {
        *(.rodata*)
    }
    
    .data : {
        *(.data*)
    }
    
    .bss : {
        *(.bss*)
        *(COMMON)
    }
}
