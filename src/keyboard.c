#include "../inc/keyboard.h"

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

//void UpdateSpecialKeys(Keyboard* keyboard, uint16_t key)
//{
//  keyboard->
//}

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
	case 0x1C : KeyPressed(&keyboard->keys[KEY_A]);
	  break;
	case 0x32 : KeyPressed(&keyboard->keys[KEY_B]);
	  break;
	case 0x21 : KeyPressed(&keyboard->keys[KEY_C]);
	  break;
	case 0x23 : KeyPressed(&keyboard->keys[KEY_D]);
	  break;
	case 0x24 : KeyPressed(&keyboard->keys[KEY_E]);
	  break;
	case 0x2B : KeyPressed(&keyboard->keys[KEY_F]);
	  break;
	case 0x34 : KeyPressed(&keyboard->keys[KEY_G]);
	  break;
	case 0x33 : KeyPressed(&keyboard->keys[KEY_H]);
	  break;
	case 0x43 : KeyPressed(&keyboard->keys[KEY_I]);
	  break;
	case 0x3B : KeyPressed(&keyboard->keys[KEY_J]);
	  break;
	case 0x42 : KeyPressed(&keyboard->keys[KEY_K]);
	  break;
	case 0x4B : KeyPressed(&keyboard->keys[KEY_L]);
	  break;
	case 0x3A : KeyPressed(&keyboard->keys[KEY_M]);
	  break;
	case 0x31 : KeyPressed(&keyboard->keys[KEY_N]);
	  break;
	case 0x44 : KeyPressed(&keyboard->keys[KEY_O]);
	  break;
	case 0x4D : KeyPressed(&keyboard->keys[KEY_P]);
	  break;
	case 0x15 : KeyPressed(&keyboard->keys[KEY_Q]);
	  break;
	case 0x2D : KeyPressed(&keyboard->keys[KEY_R]);
	  break;
	case 0x1B : KeyPressed(&keyboard->keys[KEY_S]);
	  break;
	case 0x2C : KeyPressed(&keyboard->keys[KEY_T]);
	  break;
	case 0x3C : KeyPressed(&keyboard->keys[KEY_U]);
	  break;
	case 0x2A : KeyPressed(&keyboard->keys[KEY_V]);
	  break;
	case 0x1D : KeyPressed(&keyboard->keys[KEY_W]);
	  break;
	case 0x22 : KeyPressed(&keyboard->keys[KEY_X]);
	  break;
	case 0x35 : KeyPressed(&keyboard->keys[KEY_Y]);
	  break;
	case 0x1A : KeyPressed(&keyboard->keys[KEY_Z]);
	  break;
	case 0x45 : KeyPressed(&keyboard->keys[KEY_ZERO]);
	  break;
	case 0x16 : KeyPressed(&keyboard->keys[KEY_ONE]);
	  break;
	case 0x1E : KeyPressed(&keyboard->keys[KEY_TWO]);
	  break;
	case 0x26 : KeyPressed(&keyboard->keys[KEY_THREE]);
	  break;
	case 0x25 : KeyPressed(&keyboard->keys[KEY_FOUR]);
	  break;
	case 0x2E : KeyPressed(&keyboard->keys[KEY_FIVE]);
	  break;
	case 0x36 : KeyPressed(&keyboard->keys[KEY_SIX]);
	  break;
	case 0x3D : KeyPressed(&keyboard->keys[KEY_SEVEN]);
	  break;
	case 0x3E : KeyPressed(&keyboard->keys[KEY_EIGHT]);
	  break;
	case 0x46 : KeyPressed(&keyboard->keys[KEY_NINE]);
	  break;
	case 0x0E : KeyPressed(&keyboard->keys[KEY_BACK_TICK]);
	  break;
	case 0x4E : KeyPressed(&keyboard->keys[KEY_HYPHEN]);
	  break;
	case 0x55 : KeyPressed(&keyboard->keys[KEY_EQUAL]);
	  break;
	  //More keypresses go here.
	  //Also we need to add in key releases.
	}
    }
}
