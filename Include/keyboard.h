#include "Tools/io.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H
#define NUM_KEYS 47


enum KEY_VALUES
  {
    KEY_BACK_TICK = 0,
    KEY_ONE = 1,
    KEY_TWO = 2,
    KEY_THREE = 3,
    KEY_FOUR = 4,
    KEY_FIVE = 5,
    KEY_SIX = 6,
    KEY_SEVEN = 7,
    KEY_EIGHT = 8,
    KEY_NINE = 9,
    KEY_ZERO = 10,
    KEY_HYPHEN = 11,
    KEY_EQUAL = 12,
    KEY_Q = 13,
    KEY_W = 14,
    KEY_E = 15,
    KEY_R = 16,
    KEY_T = 17,
    KEY_Y = 18,
    KEY_U = 19,
    KEY_I = 20,
    KEY_O = 21,
    KEY_P = 22,
    KEY_OPEN_BRACKET = 23,
    KEY_CLOSE_BRACKET = 24,
    KEY_BACK_SLASH = 25,
    KEY_A = 26,
    KEY_S = 27,
    KEY_D = 28,
    KEY_F = 29,
    KEY_G = 30,
    KEY_H = 31,
    KEY_J = 32,
    KEY_K = 33,
    KEY_L = 34,
    KEY_SEMICOLON = 35,
    KEY_SINGLE_QUOTE = 36,
    KEY_Z = 37,
    KEY_X = 38,
    KEY_C = 39,
    KEY_V = 40,
    KEY_B = 41,
    KEY_N = 42,
    KEY_M = 43,
    KEY_COMMA = 44,
    KEY_PERIOD = 45,
    KEY_FORWARD_SLASH = 46,
  };

/*3byte struct.*/
typedef struct
{
  char key;
  char modkey;
  bool ispressed;
} Key;

/*Probably a 12byte struct, but I'm unsure.*/
typedef struct
{
  uint8_t scan_type;
  uint16_t special_keys;
  /* modifier layout.
     These bits are meant to be read from right to left.
     bit | key
     ---------
      0  | Caps Lock
      0  | Left Shift
      0  | Left Control
      0  | Left Alt
      0  | Right Shift
      0  | Right Control
      0  | Right Alt
      0  | Space
      0  | Tab
      0  | Backspace
      0  | Delete
      0  | Enter
      0  | Up
      0  | Down
      0  | Left
      0  | Right
  */
  
  uint16_t data;
  uint16_t controller;
  Key keys[NUM_KEYS];
} Keyboard;


void CreateKey(Key* key, char keyd, char modkey);
void CreateKeyboard(Keyboard* keyboard);
void KeyNotPressed(Key* key);
void KeyPressed(Key* key);

#endif // KEYBOARD_H
