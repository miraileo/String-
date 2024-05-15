#include "s21_string.h"

char* s21_strstr(char* str1, char* str2) {
  int str1_len = s21_strlen(str1);
  int str2_len = s21_strlen(str2);

  for (int i = 0; i <= str1_len - str2_len; i++) {
    int j;
    for (j = 0; j < str2_len; j++) {
      if (str1[i + j] != str2[j]) {
        break;
      }
    }
    if (j == str2_len) {
      return (char*)&str1[i];
    }
  }
  return S21_NULL;
}