#include "kernel.h"

/* Execution begins here. */

void kernel_main(void)
{
  VgaBuffer buffer;
  CreateVgaBuffer(&buffer, 75, 80, CreateVgaColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
  while(true)
  {
    VgaWriteString(&buffer, "shit", Strlen("shit"));
  }
}

