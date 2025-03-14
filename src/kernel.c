#include "source.h"
#include "keyboard.h"

void _start (void){
    main();
}

void main(void)
{
    unsigned short* terminal_buffer = (unsigned short*) VGA_ADDRESS;
    clear_screen();
    print_string("Kernel loaded.", WHITE_COLOR);
    print_string("[KokKernel Version 1]", YELLOW);
    print_string("Ata Ilhan Kokturk - 2025", YELLOW);
    while (1) {
        if (vga_index > 26*80) clear_screen();
        keyboard_handler();
    }
    return;
}