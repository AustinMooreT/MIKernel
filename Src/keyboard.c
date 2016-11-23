#include "../Include/keyboard.h"

/* I personally don't really like a lot of the implementation details for ps2 keyboards.
   If you can improve upon this without breaking compatiblity in the rest of the kernel please do. */

void CreateKey(Key* keyc, char key, char modkey)
{
  keyc->key = key;
  keyc->modkey = modkey;
  keyc->ispressed = false;
}

void CreateKeyboard(Keyboard* keyboard)
{
  if(keyboard == NULL)
    return;
  
  keyboard->data = (uint16_t)0x60; //0x60 is the data port for PS/2 keyboards.
  keyboard->controller = (uint16_t)0x64; //0x64 is the controller  port for PS/2 keyboards.

  outb(keyboard->controller, 0xF0); //Tell the keyboard we want to set scancodes.

  if(inb(keyboard->data) == 0xFE) //Scan code is already set.
    {
      outb(keyboard->controller, 0xFE); //Sending 0xFE (try again) to the controller.
      keyboard->scan_type = inb(keyboard->data); //Reading the preset scancode.
    }
  else if(inb(keyboard->data) == 0xFA) //Keyboard acknowledged our request for scancodes.
    {
      outb(keyboard->controller, 0b00000010); //Set keyboard to scancode 1.
      keyboard->scan_type = 2;
    }

  keyboard->special_keys = 0b0000000000000000; // Init the special keys
  
  /*Init keystates in the keyboard struct.
    I'd like to find a way to clean this up,
    and shorten it. */
  CreateKey(&keyboard->keys[0], '`', '~');
  CreateKey(&keyboard->keys[1], '1', '!');
  CreateKey(&keyboard->keys[2], '2', '@');
  CreateKey(&keyboard->keys[3], '3', '#');
  CreateKey(&keyboard->keys[4], '4', '$');
  CreateKey(&keyboard->keys[5], '5', '%');
  CreateKey(&keyboard->keys[6], '6', '^');
  CreateKey(&keyboard->keys[7], '7', '&');
  CreateKey(&keyboard->keys[8], '8', '*');
  CreateKey(&keyboard->keys[9], '9', '(');
  CreateKey(&keyboard->keys[10], '0', ')');
  CreateKey(&keyboard->keys[11], '-', '_');
  CreateKey(&keyboard->keys[12], '=', '+');
  CreateKey(&keyboard->keys[13], 'q', 'Q');
  CreateKey(&keyboard->keys[14], 'w', 'W');
  CreateKey(&keyboard->keys[15], 'e', 'E');
  CreateKey(&keyboard->keys[16], 'r', 'R');
  CreateKey(&keyboard->keys[17], 't', 'T');
  CreateKey(&keyboard->keys[18], 'y', 'Y');
  CreateKey(&keyboard->keys[19], 'u', 'U');
  CreateKey(&keyboard->keys[20], 'i', 'I');
  CreateKey(&keyboard->keys[21], 'o', 'O');
  CreateKey(&keyboard->keys[22], 'p', 'P');
  CreateKey(&keyboard->keys[23], '[', '{');
  CreateKey(&keyboard->keys[24], ']', '}');
  CreateKey(&keyboard->keys[25], '\\','|');
  CreateKey(&keyboard->keys[26], 'a', 'A');
  CreateKey(&keyboard->keys[27], 's', 'S');
  CreateKey(&keyboard->keys[28], 'd', 'D');
  CreateKey(&keyboard->keys[29], 'f', 'F');
  CreateKey(&keyboard->keys[30], 'g', 'G');
  CreateKey(&keyboard->keys[31], 'h', 'H');
  CreateKey(&keyboard->keys[32], 'j', 'J');
  CreateKey(&keyboard->keys[33], 'k', 'K');
  CreateKey(&keyboard->keys[34], 'l', 'L');
  CreateKey(&keyboard->keys[35], ';', ':');
  CreateKey(&keyboard->keys[36], '\'', '\"');
  CreateKey(&keyboard->keys[37], 'z', 'Z');
  CreateKey(&keyboard->keys[38], 'x', 'X');
  CreateKey(&keyboard->keys[39], 'c', 'C');
  CreateKey(&keyboard->keys[40], 'v', 'V');
  CreateKey(&keyboard->keys[41], 'b', 'B');
  CreateKey(&keyboard->keys[42], 'n', 'N');
  CreateKey(&keyboard->keys[43], 'm', 'M');
  CreateKey(&keyboard->keys[44], ',', '<');
  CreateKey(&keyboard->keys[45], '.', '>');
  CreateKey(&keyboard->keys[46], '/', '?');
  
  outb(keyboard->controller, 0xF4); //Enable scanning.
}

void KeyNotPressed(Key* key)
{key->ispressed = false;}
void KeyPressed(Key* key)
{key->ispressed = true;}

void UpdateSpecialKeys(Keyboard* keyboard, uint16_t key)
{
  keyboard->
}

void PollKeyboard(Keyboard* keyboard)
{
  if(keyboard == NULL)
    return;

  char scancode = inb(keyboard->data);
  if(keyboard->scan_type == 1)
    {
      /* It's very unlikely the keyboard will use scan_type 1,
	 but I would like to add them in at some point. */
    }
  else if(keyboard->scan_type == 2)
    {
      switch (scancode)
	{
	case : 
    }
}
