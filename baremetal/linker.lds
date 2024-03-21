ENTRY(_start)

SECTIONS {
    . = 0x0;
    .header : ALIGN(16) {
        /* Register File*/
        LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0)
        LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0)
        LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0)
        LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0)

        /* Entry Point */
        LONG(_start)
    }

    .text : ALIGN(16) {
        *(.text)
    }
    .rodata : ALIGN(16) {
        *(.rodata)
    }
}
