#include "source.h"

unsigned short* terminal_buffer = (unsigned short*) VGA_ADDRESS;
unsigned int vga_index = 0;

void clear_screen(void) {
    for (int i = 0; i < 80 * 25; i++) {
        terminal_buffer[i] = (WHITE_COLOR << 8) | ' ';
    }
    vga_index = 0;
}

void print_char(char c, unsigned char color) {
    if (c == '\n') {
        vga_index += 80 - (vga_index % 80);
    } else {
        terminal_buffer[vga_index] = (color << 8) | c;
        vga_index++;
    }
}

void print_string(char* str, unsigned char color) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i], color);
    }
    print_char('\n', color);
}