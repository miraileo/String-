#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *res = (char *)str;
  for (int i = 0; i < (int)n; i++) {
    res[i] = c;
  }
  return res;
}