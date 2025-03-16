#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xB8000   

#define BLACK 0
#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE_COLOR 15

extern unsigned short* terminal_buffer; // Sadece bildiriyoruz!
extern unsigned int vga_index; // Tanımlama burada yok!

void print_string(char* str, unsigned char color);
void print_char(char str, unsigned char color);
void clear_screen(void);

#endif