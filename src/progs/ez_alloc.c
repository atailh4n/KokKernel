#include "memorymgr.h"
#include "drivers/vga.h"

void export_ez_alloc() {
    ez_alloc();
}

void ez_alloc() {
    void *ptr = memory_alloc(6, 1);
    print_string("Allocating size of 10.", YELLOW);
    if (ptr != NULL)
    {
        print_address(ptr);
    }
    else
    {
        print_string("Allocation fail.", RED);
    }
    char *char_ptr = (char *)ptr;
    for (int i = 0; i < 3; i++)
    {
        char_ptr[i] = 'A' + i;
    }
    print_string("Writing...", WHITE_COLOR);

    for (int i = 0; i < 3; i++) {
        char value = char_ptr[i];
        print_char(value, WHITE_COLOR);
    }
    print_char('\n', BLACK);

    memory_free(ptr, 1);
}