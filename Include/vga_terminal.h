#include "Tools/io.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef VGATERM_H
#define VGATERM_H

/* The size of this struct will varry betwenn 64 bit and 32 bit compiled code.
   on a 32 bit system the size will be 20 bytes.
   on a 64 bit system the size will be 40 bytes. */
typedef struct
{
  uint8_t color;
  uint16_t* buffer;
  size_t HEIGHT;
  size_t WIDTH;
  size_t row;
  size_t column;
} VgaBuffer;

/* Hardware text mode color constants.
   Each these refer to a color value that is r*/
enum VGA_COLOR {
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
uint8_t CreateVgaColor(enum VGA_COLOR background, enum VGA_COLOR foreground);

/* This function returns a 2 byte integer,
   in which the first byte is a single byte color with foreground and background, and
   the second byte is a single byte character */
uint16_t CreateVgaChar(unsigned char character, uint8_t color);

/* This function prepares a vga buffer to be written.
   The buffer will start completely blank.
   NOTE If the same starting parameters are passed this function can be used to clear the buffer. */
void CreateVgaBuffer(VgaBuffer* buffer, const size_t width, const size_t height, uint8_t color);

/* Writes a character to a specified x and y coordinate in provided buffer,
   it's best to use the other write char method. */
void VgaWriteCharRaw(VgaBuffer* buffer, char character, size_t x, size_t y);

/* Updates the text buffers cursor to the buffers current row and column */
void VgaUpdateCursor(VgaBuffer* buffer);

/* Writes a character to the provided buffer at the current row/column.*/
void VgaWriteChar(VgaBuffer* buffer, char character);

/* Writes a string to the provided buffer buffer at the current row/column*/
void VgaWriteString(VgaBuffer* buffer, char* str, size_t length);

/* Initiates the default buffer */
void VgaInit();

/* This is the global uninitialized buffer. */
extern VgaBuffer default_buffer_k;

/*Prints a message directly to the vga out*/
void printk(char* message);

#endif //VGATERM_H
