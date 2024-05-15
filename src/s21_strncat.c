#include <string.h>

#include "s21_string.h"
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int size = s21_strlen(dest);
  for (int i = size; i < size + (int)n; i++) {
    dest[i] = src[i - size];
  }
  return dest;
}