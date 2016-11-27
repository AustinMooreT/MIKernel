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

/* This function is quite bad, and assumes the state of a lot of the vga hardware.*/
void VgaUpdateCursor(VgaBuffer* buffer)
{
  uint16_t current_position = (buffer->row * 80) + buffer->column;
  outb(0x3D4, 0x0F);
  outb(0x3D5, (current_position & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, ((current_position >> 8) & 0xFF));
}

void VgaWriteChar(VgaBuffer* buffer, char character)
{
  if(buffer == NULL)
    return;
  if(character == '\n') //Checks for newline and handles it appropriately.
    {
      buffer->row++;
      buffer->column = 0;
    }
  else if(character == '\b') //Checks for backspace and handles it.
    {
      buffer->column--;
      VgaWriteChar(buffer, ' '); //Erases the previous character
      //loop to move all of the characters back.
      for(size_t y = buffer->row; y < buffer->HEIGHT; y++)
	{for(size_t x = buffer->column; x < buffer->WIDTH; x++)
	    {
	      const size_t current = y * buffer->WIDTH + x;
	      const size_t new = y * buffer->WIDTH + (x - 1);
	      buffer->buffer[new] = buffer->buffer[current];
	    }
	}
      buffer->column--; //Moves the cursor back one.
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
  VgaUpdateCursor(buffer);
}
void VgaWriteString(VgaBuffer* buffer, char* str, size_t length)
{
  if(buffer == NULL)
    return;
  
  for(size_t i = 0; i < length; i++)
    VgaWriteChar(buffer, str[i]);
}

void VgaCursor()
{
  if(default_buffer_k.color == CreateVgaColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE))
    {
      const size_t index = default_buffer_k.row * default_buffer_k.WIDTH + default_buffer_k. column;
      default_buffer_k.buffer[index] =
	default_buffer_k.buffer[index] | (uint16_t)CreateVgaColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE) << 8;
    }
}

void VgaInit()
{CreateVgaBuffer(&default_buffer_k, 80, 25, CreateVgaColor(VGA_COLOR_BLUE, VGA_COLOR_WHITE));}

VgaBuffer default_buffer_k;

void printk(char* str)
{VgaWriteString(&default_buffer_k, str, Strlen(str));}
