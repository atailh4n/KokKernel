#include "drivers/vga.h"

unsigned short* terminal_buffer = (unsigned short*) VGA_ADDRESS;
unsigned int vga_index = 0;

/*
    Clears all of the screen
*/
void clear_screen(void) {
    for (int i = 0; i < 80 * 25; i++) {
        terminal_buffer[i] = (WHITE_COLOR << 8) | ' ';
    }
    vga_index = 0;
}

/*
    For printing next indx a char
    char c - a char to print
    unsigned char color - a color for printing char
*/
void print_char(char c, unsigned char color) {
    if (c == '\n') {
        vga_index += 80 - (vga_index % 80);
    } else {
        terminal_buffer[vga_index] = (color << 8) | c;
        vga_index++;
    }
}

/*
    For printing full text, actually print_char but recursively.
    char* str - chars to print
    unsigned char color - a color for printing char
*/
void print_string(char* str, unsigned char color) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i], color);
    }
    print_char('\n', color);
}