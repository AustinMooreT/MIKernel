#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef IO_H
#define IO_H

/* Returns 1 byte value at a supplied io location. */
uint8_t inb(uint16_t port);

/* Writes a 1 byte value at a supplied io location. */
void outb(uint16_t port, uint8_t value);

#endif // IO_H
