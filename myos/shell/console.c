#include "console.h"

void clear_terminal() {
	char* const VGA_BUFFER = (char*) 0xb8000;
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        	VGA_BUFFER[i * VG_BYTES_PER_CHARACTER] = '\0'; 
        	VGA_BUFFER[i * VG_BYTES_PER_CHARACTER + 1] = 0x07;
    	}
}


void print_character(char c) {
    	static int offset = 0;
    	char* const VGA_BUFFER = (char*) 0xb8000;

    	if (c == '\n') {
        	// Calculate the remaining characters in the current line, kept this if
        	// I was supposed to call print_character for print_string
        	int remaining_chars = VGA_WIDTH - (offset / (VG_BYTES_PER_CHARACTER * VGA_WIDTH));
        	// Fill the remaining characters with null characters.
        	for (int i = 0; i < remaining_chars; i++) {
            		VGA_BUFFER[offset + i * VG_BYTES_PER_CHARACTER] = '\0';
            		VGA_BUFFER[offset + i * VG_BYTES_PER_CHARACTER + 1] = 0x07; // Set style byte
        	}
        	// Move to the beginning of the next line
        	offset = ((offset / (VG_BYTES_PER_CHARACTER * VGA_WIDTH)) + 1) * VG_BYTES_PER_CHARACTER * VGA_WIDTH;
    	} else {
        	// Print the character
        	VGA_BUFFER[offset] = c;
        	VGA_BUFFER[offset + 1] = 0x07; // Set style byte
        	offset += VG_BYTES_PER_CHARACTER;
    	}
    	
    	/* THIS BLOCK WILL NEED TO BE INCLUDED IF I WAS SUPPOSED TO CALL PRINT_CHARACTER FOR PRINT_STRING. I am using offset in this code 
    	because it allows me to repeatedly call the function. However, in this current implementation it is not needed and this implementation of 
    	offset does not work properly. I end up writing over a line when i reach the end of it it seems like. However, in the 
    	example you gave us, to print hello world today, it works since i don't end up printing something long. 
    	
    	// Check if our offset is at the end of the line
    	if (offset >= VGA_WIDTH * VGA_HEIGHT * VG_BYTES_PER_CHARACTER) {
        	for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1) * VG_BYTES_PER_CHARACTER; i++) {
            		VGA_BUFFER[i] = VGA_BUFFER[i + VGA_WIDTH * VG_BYTES_PER_CHARACTER];
        	}
        	// Clear the last line
        	for (int i = VGA_WIDTH * (VGA_HEIGHT - 1) * VG_BYTES_PER_CHARACTER; i < VGA_WIDTH * VGA_HEIGHT * VG_BYTES_PER_CHARACTER; i++) {
            		VGA_BUFFER[i] = '\0';
        	}
        	offset = VGA_WIDTH * (VGA_HEIGHT - 1) * VG_BYTES_PER_CHARACTER;
    	}
    	
    	*/

}


/*
void print_string(char* str) {
	while (*str != '\0') {
		print_character(*str);
		str++;
	}
}

void print_line(char* str) {
	print_character('\n');
	print_string(str);
	print_character('\n');
}
*/


void print_string(char* str) {
    	while (*str != '\0') {
        	print_character(*str);
        	str++;
    	}	
}

void print_line(char* str) {
    	print_character('\n');
    	while (*str != '\0') {
        	print_character(*str);
        	str++;
    	}
    	print_character('\n');
}

