#!/bin/bash

rm myos.bin

i686-elf-as /home/maurice/Code/C/MIKernel/src/boot_code/boot.s -o boot.o

i686-elf-gcc -c /home/maurice/Code/C/MIKernel/kernel.c /home/maurice/Code/C/MIKernel/src/keyboard.c /home/maurice/Code/C/MIKernel/src/vga_terminal.c /home/maurice/Code/C/MIKernel/src/tools/io.c /home/maurice/Code/C/MIKernel/src/tools/string.c -ffreestanding -O2 -Wall -Wextra

i686-elf-gcc -T /home/maurice/Code/C/MIKernel/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib *.o -lgcc

rm *.o

qemu-system-i386 -kernel myos.bin
