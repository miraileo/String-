#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int flag = 0;
  int count = 0;
  if (str1[0] == '\0' || str2[0] == '\0') return s21_strlen(str1);
  for (int i = 0; str1[i] != '\0' && !flag; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
    }
    count++;
  }
  return count - 1;
}