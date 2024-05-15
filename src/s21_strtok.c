#include "s21_string.h"

char* s21_strtok(char* str, char* delimiters) {
  static char* nextToken = 0;

  if (str) {
    nextToken = str;
  } else if (!nextToken) {
    return S21_NULL;
  }

  while (*nextToken != '\0' && s21_strchr(delimiters, *nextToken)) {
    nextToken++;
  }

  if (*nextToken == '\0') {
    nextToken = S21_NULL;
    return S21_NULL;
  }

  char* c = nextToken;
  while (*nextToken != '\0' && !s21_strchr(delimiters, *nextToken)) {
    nextToken++;
  }

  if (*nextToken != '\0') {
    *nextToken = '\0';
    nextToken++;
  } else
    nextToken = S21_NULL;

  return (void*)c;
}