#include "console.h"



void set_terminal_font_color(VGA_Color col) {
	terminal_font_color = col;
}

 

void set_terminal_background_color(VGA_Color col) {
	terminal_background_color = col;
}


void clear_terminal() {
    char* const VGA_BUFFER = (char*) 0xb8000;
    // Clear the entire VGA buffer by setting all characters to null
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_BUFFER[i * VG_BYTES_PER_CHARACTER] = '\0'; 
        VGA_BUFFER[i * VG_BYTES_PER_CHARACTER + 1] = 0x07; // Set style byte
    }
    // Reset the offset to the beginning of the buffer
    terminal_pointer = 0;
}



void print_character(char c) {

	print_character_with_color(c, terminal_background_color, terminal_font_color);

}

void print_string(char* str) {
	
	print_string_with_color(str, terminal_background_color, terminal_font_color);
	
}

void print_line(char* str) {

	print_line_with_color(str, terminal_background_color, terminal_font_color);

}


void print_line_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {

	print_string_with_color(str, bg_color, font_color);

	print_character_with_color('\n', bg_color, font_color);

}

void print_string_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {

	for (int i=0; str[i] != '\0'; i++) {

		print_character_with_color(str[i], bg_color, font_color);

	}

}

void print_character_with_color(char c, VGA_Color bg_color, VGA_Color font_color) {
    char* const VGA_BUFFER = (char*) 0xb8000;
    // Check if character is newline
    if (c == '\n') {
        // Move to the beginning of the next line
        terminal_pointer = ((terminal_pointer / (VG_BYTES_PER_CHARACTER * VGA_WIDTH)) + 1) * VG_BYTES_PER_CHARACTER * VGA_WIDTH;
    } else {
        // Print the character at the current terminal pointer (offset)
        VGA_BUFFER[terminal_pointer] = c;
        VGA_BUFFER[terminal_pointer + 1] = (bg_color << 4) | font_color; // Set style byte
        terminal_pointer += VG_BYTES_PER_CHARACTER;
    }
}

