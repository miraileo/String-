#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;
  int srcLen = s21_strlen(src);
  char *result = S21_NULL;
  int trim_charsLen = s21_strlen(trim_chars);
  int startLen = 0;
  int endLen = 0;
  int tmp = 0;

  if (srcLen > 0) {
    for (int i = 0; i < srcLen; i++) {
      tmp = startLen;
      for (int j = 0; j < trim_charsLen; j++) {
        if (src[i] == trim_chars[j]) {
          startLen++;
          break;
        }
      }
      if (startLen == tmp) break;
    }

    for (int i = srcLen - 1; i >= 0; i--) {
      tmp = endLen;
      for (int j = 0; j < trim_charsLen; j++) {
        if (src[i] == trim_chars[j]) {
          endLen++;
          break;
        }
      }
      if (endLen == tmp) break;
    }
  }

  result = calloc(srcLen - endLen - startLen + 1, sizeof(char));
  if (result != S21_NULL) {
    s21_strncpy(result, src + startLen, srcLen - endLen - startLen);
  }
  return (void *)result;
}
