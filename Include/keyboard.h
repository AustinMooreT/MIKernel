#include "Tools/io.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H
#define NUM_KEYS 255

typedef struct
{
  char key;
  char modkey;
  bool ispressed;
} Key;

typedef struct
{
  uint16_t data;
  uint16_t controller;
  uint8_t scan_type;
  Key keys[NUM_KEYS];
  uint8_t modifiers;
} Keyboard;



void CreateKeyboard(Keyboard* keyboard);

#endif // KEYBOARD_H
