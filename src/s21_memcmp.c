#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *resStr1 = str1;
  const unsigned char *resStr2 = str2;
  int result = 0;
  for (int i = 0; i < (int)n; i++) {
    if (resStr1[i] > resStr2[i]) result = 1;
    if (resStr1[i] < resStr2[i]) result = -1;
    if (result == -1 || result == 1) break;
  }
  return result;
}