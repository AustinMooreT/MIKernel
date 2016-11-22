#include "Include/vga_terminal.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
void kernel_main(void)
{
  const size_t VGA_WIDTH = 80;
  const size_t VGA_HEIGHT = 25;
  
  size_t vga_row = 0;
  size_t vga_column = 0;

  uint16_t* vga_buffer =GetVgaBuffer
    (VGA_WIDTH,
     VGA_HEIGHT,
     VgaColorInt(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
  
  VgaWriteString
    (vga_buffer,
     &VGA_WIDTH,
     &VGA_HEIGHT,
     "MIKernel version meme",
     21,
     &vga_row,
     &vga_column,
     VgaColorInt(VGA_COLOR_DARK_GREY, VGA_COLOR_CYAN));

}
