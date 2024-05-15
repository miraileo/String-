#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = c == '\0' ? "" : S21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
    str++;
  }
  return result;
}