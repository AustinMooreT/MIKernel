#include "../Include/keyboard.h"

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
      keyboard->scan_type = inb(keyboard->data);
    }
  else if(inb(keyboard->data) == 0xFA) //Keyboard acknowledged our request for scancodes.
    {
      outb(keyboard->controller, 0b00000010); //Set keyboard to scancode 1.
      keyboard->scan_type = 2;
    }
  else
    {
      keyboard->scan_type = 255; //This is bad.
    }

  //add code for enumerating the keyboard.
  
  outb(keyboard->controller, 0xF4); //Enable scanning.
}

void PollKeyboard(Keyboard* keyboard)
{
  char scancode = inb(keyboard->data);
  if(keyboard->scan_type == 1)
    {
      //add keycode checks, and update their shit.
    }
  else if(keyboard->scan_type == 2)
    {
      //add keycode checks, and update their shit.
    }
}
