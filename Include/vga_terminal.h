#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef VGATERM_H
#define VGATERM_H

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

/* This funcion returns a byte, the first nibble of that byte represents the background.
   The second nibble is the foreground color.*/
uint8_t VgaColorInt(enum vga_color background, enum vga_color foreground);

/* This function returns a 2 byte integer in which the first byte is a single byte color with foreground and background.
   The second byte is a single byte character that.*/
uint16_t CreateVgaChar(unsigned char character, uint8_t color);

/* This function returns a pointer to the basic vga buffer.
   width and height specify the width and height of the display.
   Color is a single byte color value that contains the foreground and background.*/
uint16_t* GetVgaBuffer(size_t width, size_t height, uint8_t color);

/* Writes a character to a specified x and y coordinate, it's best to use the other write char method. */
void VgaWriteCharRaw(uint16_t* buffer, size_t* width, char character, size_t x, size_t y, uint8_t color);

/* Writes a character to a specified row and column in the buffer.*/
void VgaWriteChar(uint16_t* buffer, size_t* width, size_t* height, char character, size_t* row, size_t* column, uint8_t color);

/* Writes a string starting at a specified row or column. */
void VgaWriteString
(uint16_t* buffer,
 const size_t* width,
 const size_t* height,
 char* str,
 size_t length,
 size_t* row,
 size_t* column,
 uint8_t color);

#endif //VGATERM_H
