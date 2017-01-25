#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// see strutils.h for documentation
#include "strutils.h"


// this is from the notes
char *my_strdup(const char *s) {
  char *newstr = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(newstr, s);
  return newstr;
}


// this is modified slightly from the notes version
char *readline(void) {
  char c;
  if (scanf(" %c", &c) != 1) return NULL;
  int maxlen = 80;  
  char *str = malloc(maxlen * sizeof(char));
  int len = 0;
  do {
    str[len] = c;
    ++len;
    if (len == maxlen) {    // DOUBLE the allocated array size
      maxlen *= 2;
      str = realloc(str, maxlen * sizeof(char));
    }
    if (scanf("%c", &c) != 1) break;
  } while (c != '\n');   // read to the end of the line
  str[len] = '\0';
  // shrink the array back down to the correct size
  str = realloc(str, (len + 1) * sizeof(char));
  return str;
}


// this has been added to keep reval uncluttered
bool is_blank(const char *s) {
  while (*s) {
    if (*s != ' ') return false;
    ++s;
  }
  return true;
}
