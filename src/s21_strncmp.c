#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int comparison = 0;

  for (int i = 0; i < (int)n && comparison == 0; i++) {
    int char1 = str1[i];
    int char2 = str2[i];
    comparison = char1 - char2;
  }
  return comparison;
}