__heap_size = 0x200;
__stack_size = 0x800;

ENTRY(_start)

SECTIONS {
    . = 0x0;
    .header : ALIGN(16) {
        /* Register File*/
        LONG(0) LONG(0) LONG(_sstack) LONG(0) LONG(0) LONG(0) LONG(0) LONG(0)
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

    .heap : ALIGN( 16 ) {
        _sheap = .;
        . = . + __heap_size;
        _eheap = .;
    }

    .stack : ALIGN( 16 ) {
        _estack = .;
        . = . + __stack_size;
        _sstack = .;
    }

    PROVIDE( uarthead = 0xfb000 );
    PROVIDE( uarttail = 0xfb004 );
    PROVIDE( uartbuffer = 0xfb100 );
}
