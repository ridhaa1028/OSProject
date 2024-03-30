

void main() {

	clear_terminal();


	print_string("HELLO");

	print_line("WORLD");

	print_string("TODAY");
	//char* const VGA_BUFFER = (char*) 0xb8000;
	//char* str = "Hello World";

	//for (int i=0; str[i] != '\0'; i++) {
		//VGA_BUFFER[i*2] = str[i];
	//}

	return;
}

/*
void clear_terminal() {

	char* const VGA_BUFFER = (char*) 0xb8000;
	for (int i = 0; i < 80 * 25; i++) {
		VGA_BUFFER[i * 2] = '\0';
		VGA_BUFFER[i * 2 + 1] = 0x07;
	}
}
*/
