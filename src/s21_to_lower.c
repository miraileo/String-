#include "s21_string.h"
void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;

  char *result = calloc(s21_strlen(str) + 1, sizeof(char));

  if (result == S21_NULL) return S21_NULL;

  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      result[i] = str[i] + 32;
    } else
      result[i] = str[i];
  }

  result[i] = '\0';

  return result;
}
