#include "console.h"

// Global variable to track the current offset in the VGA buffer
static int terminal_Pointer = 0;

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
    char* const VGA_BUFFER = (char*) 0xb8000;

    // Check if character is newline
    if (c == '\n') {
        // Move to the beginning of the next line
        terminal_pointer = ((terminal_pointer / (VG_BYTES_PER_CHARACTER * VGA_WIDTH)) + 1) * VG_BYTES_PER_CHARACTER * VGA_WIDTH;
    } else {
        // Print the character at the current offset
        VGA_BUFFER[offset] = c;
        VGA_BUFFER[offset + 1] = 0x07; // Set style byte
        offset += VG_BYTES_PER_CHARACTER;
    }
}

void print_string(char* str) {
    while (*str != '\0') {
        print_character(*str);
        str++;
    }
    //AM I SUPPOSED TO MOVE TO A NEW LINE AFTER PRINTING A STRING?
}

void print_line(char* str) {
    print_character('\n'); // Move to the next line
    print_string(str);
}


