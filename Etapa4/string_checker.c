#include <unistd.h>
#include <stdio.h>
#include <string.h>

int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}