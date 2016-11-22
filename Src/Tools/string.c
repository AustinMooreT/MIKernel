#include "../../Include/Tools/string.h"

size_t Strlen(char* str)
{
  size_t count = 0;
  while(str[count])
    count++;
  return count;
}
