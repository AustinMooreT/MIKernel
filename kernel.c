#include "Include/vga_terminal.h"
#include "Include/Tools/string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main(void)
{
  VgaBuffer screen_buffer;
  CreateVgaBuffer(&screen_buffer, 75, 80, CreateVgaColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE));

  char* message = "MIKernel version: meme";
  VgaWriteString(&screen_buffer, message, Strlen(message));
}

