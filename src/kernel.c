#include "memorymgr.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"

void _start(void)
{
    clear_screen();
    memory_init();
    main();
}

void main(void)
{
    unsigned short *terminal_buffer = (unsigned short *)VGA_ADDRESS;
    print_string("Kernel loaded.", WHITE_COLOR);
    print_string("[KokKernel Version 1]", YELLOW);
    print_string("Ata Ilhan Kokturk - 2023-2025", YELLOW);

    // progs/ez_alloc.c
    unsigned int ss = 0;
    while (ss < 4)
    {
        // This is for loop cond. do not enable unless debugging
        //if (vga_index > 2000) clear_screen();
        export_ez_alloc(); // A program contiously reallocates memory.
        ss++;
    }
    
    // TODO: Fix the fucking allocated memory map controller
    //print_allc_memory_map();
    
    while (1)
    {
        keyboard_handler();
    }
    return;
}