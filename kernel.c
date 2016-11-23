#include "kernel.h"

/* Execution begins here. */

void kernel_main(void)
{
  CreateVgaBuffer(&default_buffer_k, 75, 80, CreateVgaColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
  printk("This is kernel version: meme");
}

