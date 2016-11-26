#include "../Include/vga_terminal.h"

uint8_t CreateVgaColor(enum VGA_COLOR background, enum VGA_COLOR foreground)
{
	return foreground | background << 4;
}

uint16_t CreateVgaChar(unsigned char character, uint8_t color)
{
	return (uint16_t) character | (uint16_t) color << 8;
}

void CreateVgaBuffer(VgaBuffer* buffer, size_t width, size_t height, uint8_t color) 
{
  if(buffer == NULL)
    return;
  
  buffer->buffer = (uint16_t*)0xB8000;
  buffer->HEIGHT = height;
  buffer->WIDTH = width;
  buffer->color = color;
  buffer->row = 0;
  buffer->column = 0;
  
  for(size_t y = 0; y < height; y++)
    {for(size_t x = 0; x < width; x++)
	{
	  const size_t index = y * width + x;
	  buffer->buffer[index] = CreateVgaChar(' ', color);
	}
    }
}

void VgaWriteCharRaw(VgaBuffer* buffer, char character, size_t x, size_t y)
{
  if(buffer == NULL)
    return;
  const size_t index = y * buffer->WIDTH + x;
  buffer->buffer[index] = CreateVgaChar(character, buffer->color);
}

void VgaWriteChar(VgaBuffer* buffer, char character)
{
  if(buffer == NULL)
    return;
  if(character == '\n')
    {
      buffer->row++;
      buffer->column = 0;
    }
  else
    {
      VgaWriteCharRaw(buffer, character, buffer->column, buffer->row); //Writes character to buffer.
      if(++buffer->column == buffer->WIDTH)
	{
	  buffer->column = 0;
	  if(++buffer->row == buffer->HEIGHT)
	    {
	      buffer->row = 0;
	      CreateVgaBuffer(buffer, buffer->WIDTH, buffer->HEIGHT, buffer->color); //resets the buffer to blank if full.
	    }
	}
    }
}
void VgaWriteString(VgaBuffer* buffer, char* str, size_t length)
{
  if(buffer == NULL)
    return;
  
  for(size_t i = 0; i < length; i++)
    VgaWriteChar(buffer, str[i]);
}

void VgaInit()
{CreateVgaBuffer(&default_buffer_k, 80, 25, CreateVgaColor(VGA_COLOR_BLUE, VGA_COLOR_WHITE));}

VgaBuffer default_buffer_k;
