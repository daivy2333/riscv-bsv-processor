/* Mini-OS Linker Script for RV32I */

MEMORY
{
    MEM (rwx) : ORIGIN = 0x80000000, LENGTH = 64K
}

ENTRY(_start)

SECTIONS
{
    .text : {
        *(.text.init)
        *(.text .text.*)
    } > MEM

    .rodata : {
        *(.rodata .rodata.*)
    } > MEM

    .data : {
        _data_start = .;
        *(.data .data.*)
        _data_end = .;
    } > MEM

    .bss : {
        _bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        _bss_end = .;
    } > MEM

    .stack (NOLOAD) : {
        . = ALIGN(16);
        _stack_bottom = .;
        . = . + 2K;
        _stack_top = .;
    } > MEM

    _end = .;

    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
        *(.note.*)
    }
}