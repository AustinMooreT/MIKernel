#include "../Include/vga_terminal.h"

uint8_t VgaColorInt(enum vga_color background, enum vga_color foreground)
{
	return foreground | background << 4;
}

uint16_t CreateVgaChar(unsigned char character, uint8_t color)
{
	return (uint16_t) character | (uint16_t) color << 8;
}

uint16_t* GetVgaBuffer(size_t width, size_t height, uint8_t color) 
{
  uint16_t* buffer = (uint16_t*)0xB8000;
  for(size_t y = 0; y < height; y++)
    {for(size_t x = 0; x < width; x++)
	{
	  const size_t index = y * width + x;
	  buffer[index] = CreateVgaChar(' ', color);
	}
    }
  return buffer;
}

void VgaWriteCharRaw(uint16_t* buffer, size_t* width, char character, size_t x, size_t y, uint8_t color)
{
  	const size_t index = y * *width + x;
	buffer[index] = CreateVgaChar(character, color);
}

void VgaWriteString(uint16_t* buffer, size_t* width, char* str, size_t length, size_t x, size_t y, uint8_t color)
{
  for(size_t i = 0; i < length i++)
    VgaWriteChar
      
}
