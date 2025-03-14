OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS {
    . = 1M;
    .text : ALIGN(4K) { *(.multiboot) *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss) }
}