#include "s21_string.h"

int Parser(const char *format, formatSpecs *specs) {
  int isZeroPrec = 0;
  int isWidth = 1;
  if (*format == '%') {
    while (FindSpecs(format, specs)) {
      Flags(format, specs);
      Length(format, specs);
      if (*format >= '0' && *format <= '9' && *format != '.' && isWidth) {
        if (*format == '0') {
          isZeroPrec = 1;
        }
        specs->width = Atoi(format);
        isWidth = 0;
      }
      if (*format == '.' && *(format + 1) >= '1' && *(format + 1) <= '9') {
        format++;
        specs->precision = Atoi(format);
      }
      if (*format == '.' && (*(format + 1) < '1' || *(format + 1) > '9')) {
        specs->precision = -1;
      }
      format++;
    }
  }
  return isZeroPrec;
}

int FindSpecs(const char *format, formatSpecs *specs) {
  int flag = 0;
  switch (*format) {
    case 'd':
      specs->d = 1;
      break;
    case 's':
      specs->s = 1;
      break;
    case 'c':
      specs->c = 1;
      break;
    case 'f':
      specs->f = 1;
      break;
    case 'u':
      specs->u = 1;
      break;
    default:
      flag = 1;
      break;
  }
  return flag;
}

void Flags(const char *format, formatSpecs *specs) {
  switch (*format) {
    case '+':
      specs->plus = 1;
      break;
    case '-':
      specs->minus = 1;
      break;
    case ' ':
      specs->space = 1;
      break;
  }
}

void Length(const char *format, formatSpecs *specs) {
  switch (*format) {
    case 'l':
      specs->l = 1;
      break;
    case 'L':
      specs->l = 1;
      break;
    case 'h':
      specs->h = 1;
      break;
  }
}

int Atoi(const char *format) {
  int result = 0;
  int tmp = 0;
  for (int i = 0; i < 10; i++) {
    if (*format == i + 48) {
      result = i;
      tmp = (tmp * 10) + result;
      format++;
      i = -1;
    }
  }
  return tmp;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int isZeroPrec = 0;
  int num_args = 0;
  const char *ptr = format;
  while (*ptr != '\0') {
    if (*ptr == '%' && *(ptr + 1) != '\0' && *(ptr + 1) != '%') {
      num_args++;
    }
    ptr++;
  }
  va_end(args);
  formatSpecs specs = {0};
  int counter = 0;
  while (*format != '\0') {
    if (*format != '%') {
      str[counter] = *format;
      counter++;
      format++;
    } else if (*(format + 1) == '%') {
      str[counter] = '%';
      counter++;
      format += 2;
    } else {
      InitSpecs(&specs);
      isZeroPrec = Parser(format, &specs);
      if (specs.d) {
        counter = DSpec(specs, str, counter, isZeroPrec, args);
      } else if (specs.f) {
        counter = FSpec(specs, str, counter, isZeroPrec, args);
      } else if (specs.s) {
        char *string = va_arg(args, char *);
        counter = String2String(str, counter, specs, isZeroPrec, string);
      } else if (specs.c) {
        counter = CSpec(specs, str, counter, isZeroPrec, args);
      } else if (specs.u) {
        counter = USpec(specs, str, counter, isZeroPrec, args);
      } else
        va_arg(args, int);
      while (FindSpecs(format, &specs)) {
        format++;
      }
      if (*format != '\0') format++;
    }
  }
  str[counter] = '\0';
  return counter;
}

int DSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args) {
  long int value = va_arg(args, long int);
  if (!specs.l) value = (int)value;
  if (!specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  counter = CheckFlags(str, counter, specs, value, isZeroPrec);
  counter = Precision(specs, VarLength(value), str, counter, value, isZeroPrec);
  counter = Int2String(value, str, counter);
  if (specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  return counter;
}

int FSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args) {
  long double value;
  if (!specs.l)
    value = va_arg(args, double);
  else
    value = va_arg(args, long double);
  if (!specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  counter = CheckFlags(str, counter, specs, value, isZeroPrec);
  counter = Float2String(value, str, counter, specs, isZeroPrec);
  if (specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  return counter;
}

int USpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args) {
  unsigned long int value = va_arg(args, unsigned long int);
  if (!specs.l) value = (unsigned int)value;
  if (!specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  counter = Precision(specs, VarLength(value), str, counter, value, isZeroPrec);
  counter = UnsignedInt2String(value, str, counter);
  if (specs.minus)
    counter = Width(specs, VarLength(value), str, counter, value, isZeroPrec);
  return counter;
}

int CSpec(formatSpecs specs, char *str, int counter, int isZeroPrec,
          va_list args) {
  char chr = va_arg(args, int);
  if (chr == '\0') str[counter] = '\0';
  if (!specs.minus) counter = Width(specs, 1, str, counter, -1, isZeroPrec);
  str[counter] = chr;
  counter++;
  if (specs.minus) counter = Width(specs, 1, str, counter, -1, isZeroPrec);
  return counter;
}

int Int2String(long int value, char *str, int i) {
  long int divisor = 1;
  long int num = value < 0 ? -value : value;
  if (value < 0) {
    value *= -1;
  }
  while (num / divisor >= 10) {
    divisor *= 10;
  }
  while (divisor > 0) {
    int digit = (value / divisor) % 10;
    char number = digit + 48;
    str[i] = number;
    divisor /= 10;
    i++;
  }
  return i;
}

int UnsignedInt2String(unsigned long int value, char *str, int i) {
  long int divisor = 1;
  unsigned long int num = value;
  while (num / divisor >= 10) {
    divisor *= 10;
  }
  while (divisor > 0) {
    int digit = (value / divisor) % 10;
    char number = digit + 48;
    str[i] = number;
    divisor /= 10;
    i++;
  }
  return i;
}

int Float2String(long double value, char *str, int i, formatSpecs specs,
                 int isZeroPrec) {
  if (value < 0) {
    if (!isZeroPrec || specs.minus) {
      str[i] = '-';
      i++;
    }
    value = -value;
  }
  int divisor = 10;
  int main = 1;
  double tmp = value;
  while (tmp > 10) {
    tmp /= divisor;
    main++;
  }
  i = MainPartOfFloat2String(main, specs, value, str, i);
  if (specs.precision != -1) {
    str[i] = '.';
    i++;
  }
  int count = 6;
  if (specs.precision != 0 && specs.precision != -1) count = specs.precision;
  if (specs.precision != -1) {
    i = FloatPartOfFloat2String(count, value, str, i);
  }
  return i;
}

int MainPartOfFloat2String(int main, formatSpecs specs, long double value,
                           char *str, int counter) {
  char digit;
  double number;
  for (int j = main; j > 0; j--) {
    if (specs.precision != -1)
      number = (value) / (pow(10, j - 1));
    else
      number = (round(value)) / (pow(10, j - 1));
    number = fmod(number, 10);
    digit = number + 48;
    str[counter] = digit;
    counter++;
  }
  return counter;
}

int FloatPartOfFloat2String(int count, long double value, char *str,
                            int counter) {
  char digit;
  double number;
  int numTmp = 0;
  for (int j = 0; j < count; j++) {
    value *= 10;
    number = (int)fmod(value, 10);
    if (j == count - 1) {
      value *= 10;
      numTmp = (int)fmod(value, 10);
    }
    if (numTmp < 5)
      digit = number + 48;
    else
      digit = number + 49;
    str[counter] = digit;
    counter++;
  }
  return counter;
}

int CheckFlags(char *str, int i, formatSpecs specs, double value,
               int isZeroPrec) {
  if (specs.plus && (!isZeroPrec || specs.minus)) {
    if (value > 0) {
      str[i] = '+';
      i++;
    }
  }
  if (specs.space && !specs.plus) {
    if (value > 0) {
      str[i] = ' ';
      i++;
    }
  }
  return i;
}

void InitSpecs(formatSpecs *specs) {
  specs->d = 0;
  specs->c = 0;
  specs->f = 0;
  specs->s = 0;
  specs->u = 0;
  specs->plus = 0;
  specs->minus = 0;
  specs->space = 0;
  specs->h = 0;
  specs->l = 0;
  specs->width = 0;
  specs->precision = 0;
}

int VarLength(double value) {
  int divisor = 10;
  int result = 0;
  if (value < 0) value *= (-1);
  while (value >= 10) {
    value /= divisor;
    result++;
  }
  return result + 1;
}

int Width(formatSpecs specs, int varLength, char *str, int i, double value,
          int isZeroPrec) {
  if (value < 0 && isZeroPrec && !specs.minus && !specs.c) {
    str[i] = '-';
    i++;
  }
  if (specs.plus && value > 0 && isZeroPrec && !specs.minus) {
    str[i] = '+';
    i++;
  }
  int count = 0;
  if (specs.d || specs.u) {
    count = value > 0 ? specs.width - varLength : specs.width - varLength - 1;
    if (specs.precision > varLength)
      count = count - (specs.precision - varLength);
  }
  if (specs.f) {
    count =
        value > 0 ? specs.width - varLength - 1 : specs.width - varLength - 2;
    if (specs.precision == 0)
      count -= 6;
    else
      count -= specs.precision;
  }
  if (specs.c) count = specs.width - varLength;
  if (specs.s) {
    if (specs.precision == 0) count = specs.width - varLength;
    if (specs.precision > 0)
      count = specs.precision < specs.width ? specs.width - specs.precision
                                            : specs.width - (varLength);
    if (specs.precision == -1) count = specs.width;
  }
  if ((specs.plus || specs.space) && value > 0 && !specs.s && !specs.u) count--;
  if (count > 0) {
    for (int j = 0; j < count; j++) {
      if (!isZeroPrec || specs.minus)
        str[i] = ' ';
      else
        str[i] = '0';
      i++;
    }
  }
  return i;
}

int Precision(formatSpecs specs, int varLength, char *str, int i,
              long int value, int isZeroPrec) {
  if (value < 0 && !isZeroPrec && !specs.u) {
    str[i] = '-';
    i++;
  }
  int precision = specs.precision - varLength;
  if (specs.d || specs.u) {
    if (precision > 0) {
      for (int j = 0; j < precision; j++) {
        str[i] = '0';
        i++;
      }
    }
  }
  return i;
}
int String2String(char *str, int i, formatSpecs specs, int isZeroPrec,
                  char *string) {
  if (!specs.minus) i = Width(specs, s21_strlen(string), str, i, 1, isZeroPrec);
  int count = specs.precision != 0 ? specs.precision : (int)s21_strlen(string);
  for (int j = 0; j < count; j++) {
    if (string[j] == '\0') break;
    str[i] = string[j];
    i++;
  }
  if (specs.minus) i = Width(specs, s21_strlen(string), str, i, 1, isZeroPrec);
  return i;
}