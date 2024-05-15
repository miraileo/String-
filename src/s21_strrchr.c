#include "s21_string.h"

char *s21_strrchr(char *str, int c) {
  int flag = 0;
  char *pointer = S21_NULL;

  if (c == '\0') {
    pointer = "";
  } else {
    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] == c) {
        flag = i;
      }
    }

    if (flag != 0) {
      for (int i = flag, j = 0; str[i] != '\0'; i++, j++) {
        pointer = (char *)(str + flag);
        printf("%c", pointer[i]);
      }
    }
  }
  return pointer;
}