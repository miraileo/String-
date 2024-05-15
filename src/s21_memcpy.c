#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *res = (char *)src;
  char *resDest = (char *)dest;
  for (int i = 0; i < (int)n; i++) {
    resDest[i] = res[i];
  }
  return resDest;
}