#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
typedef unsigned long int s21_size_t;
#define S21_NULL ((void *)0)

void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_memchr(const void *s, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
char *strchr(const char *str, int c);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
char *s21_strtok(char *str, char *delimiters);
char *s21_strstr(char *str1, char *str2);
char *s21_strerror(int errnum);
typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int l;
  int h;
  int precision;
  int d;
  int u;
  int s;
  int f;
  int c;
} formatSpecs;

int FindSpecs(const char *format, formatSpecs *specs);
int Width(formatSpecs specs, int varLength, char *str, int i, double value,
          int isZeroPrec);
int VarLength(double value);
int Parser(const char *format, formatSpecs *specs);
void Flags(const char *format, formatSpecs *specs);
int Atoi(const char *format);
void Length(const char *format, formatSpecs *specs);
int s21_sprintf(char *str, const char *format, ...);
int Int2String(long int value, char *str, int i);
int CheckFlags(char *str, int i, formatSpecs specs, double value,
               int isZeroPrec);
int Precision(formatSpecs specs, int varLength, char *str, int i,
              long int value, int isZeroPrec);
void InitSpecs(formatSpecs *specs);
int Float2String(long double value, char *str, int i, formatSpecs specs,
                 int isZeroPrec);
int String2String(char *str, int i, formatSpecs specs, int isZeroPrec,
                  char *string);
int UnsignedInt2String(unsigned long int value, char *str, int i);
int MainPartOfFloat2String(int main, formatSpecs specs, long double value,
                           char *str, int counter);
int FloatPartOfFloat2String(int count, long double value, char *str,
                            int counter);
int DSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args);
int FSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args);
int USpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args);
int CSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args);