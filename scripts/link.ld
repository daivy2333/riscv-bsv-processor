/* scripts/link.ld */
OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS {
    .text : {
        *(.text._start)
        *(.text)
    } > RAM
    
    .data : { *(.data) } > RAM
    .bss : { *(.bss) } > RAM
    
    _end = .;
}