#include "inc/kernel.h"

/* Execution begins here. */

void kernel_main(void) {
  VgaInit();
  printk("MIKernel Version: 0.0.1\n");
  printk("Dank Memes");
  char* test = (char*)0x00100000;
  test[0] = 'd';
  test[1] = 'i';
  test[2] = 'c';
  test[3] = 'k';
  test[4] = '\0';
  printk(test);
  while(true) {
  }
}

