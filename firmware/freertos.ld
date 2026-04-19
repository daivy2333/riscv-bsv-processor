/* FreeRTOS Linker Script for RV32I Processor
 *
 * Memory Layout (Harvard Architecture):
 * - IMem: 32KB @ 0x80000000 (instruction fetch)
 * - DMem: 32KB @ 0x80000000 (load/store)
 *
 * Note: IMem and DMem have overlapping addresses but are physically separate.
 */

MEMORY
{
    IMEM (rx)  : ORIGIN = 0x80000000, LENGTH = 32K
    DMEM (rwx) : ORIGIN = 0x80000000, LENGTH = 32K
}

ENTRY(_start)

SECTIONS
{
    /* Code section - goes to IMem */
    .text : {
        *(.text.init)    /* Startup code first */
        *(.text .text.*)
    } > IMEM

    /* Read-only data - goes to DMem */
    .rodata : {
        *(.rodata .rodata.*)
    } > DMEM

    /* Initialized data - goes to DMem */
    .data : {
        _data_start = .;
        *(.data .data.*)
        _data_end = .;
    } > DMEM

    /* Uninitialized data - goes to DMem */
    .bss : {
        _bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        _bss_end = .;
    } > DMEM

    /* FreeRTOS heap - goes to DMem */
    .heap (NOLOAD) : {
        . = ALIGN(8);
        _heap_start = .;
        . = . + 16K;  /* 16KB FreeRTOS heap */
        _heap_end = .;
    } > DMEM

    /* Stack - goes to DMem at end */
    .stack (NOLOAD) : {
        . = ALIGN(16);
        _stack_bottom = .;
        . = . + 4K;  /* 4KB stack */
        _stack_top = .;
    } > DMEM

    /* End of used memory */
    _end = .;

    /* Discard unwanted sections */
    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
        *(.note.*)
    }
}