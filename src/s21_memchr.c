#include "s21_string.h"

void *s21_memchr(const void *s, int c, s21_size_t n) {
  const unsigned char *res = n == 0 ? 0 : s;
  for (int i = 0; i < (int)n; i++) {
    if (c == res[i]) {
      res += i;
      break;
    }
    if (i == (int)n - 1) {
      res = S21_NULL;
    }
  }
  return (void *)res;
}
