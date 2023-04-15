#include "cstring.h"

size_t Strlen(const char* str) {
  size_t len = 0;
  while (*str != 0) {
    ++len;
    ++str;
  }

  return len;
}

int Strcmp(const char* first, const char* second) {
  while ((*first == *second) && (*first != 0) && (*second != 0)) {
    ++first;
    ++second;
  }

  return *first - *second;
}

int Strncmp(const char* first, const char* second, size_t count) {
  while ((count > 0) && (*first == *second) && (*first != 0) && (*second != 0)) {
    ++first;
    ++second;
    --count;
  }

  return ((count != 0) ? *first - *second : 0);
}

char* Strcpy(char* dest, const char* src) {
  char* curr = dest;
  while (*src != 0) {
    *curr = *src;
    ++curr;
    ++src;
  }

  *curr = '\0';
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* curr = dest;
  while (*src != 0 && (count != 0)) {
    *curr = *src;
    ++curr;
    ++src;
    --count;
  }

  while (count > 0) {
    *curr = '\0';
    ++curr;
    --count;
  }

  return dest;
}

char* Strcat(char* dest, const char* src) {
  int des_len = Strlen(dest);
  int src_len = Strlen(src);

  for (int i = des_len; i < des_len + src_len; ++i) {
    dest[i] = src[i - des_len];
  }

  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  int des_len = Strlen(dest);
  int src_len = Strlen(src);
  int k = count;

  if (k > src_len) {
    return Strcat(dest, src);
  }

  for (int i = des_len; i < des_len + k; ++i) {
    dest[i] = src[i - des_len];
  }

  return dest;
}

const char* Strchr(const char* str, char symbol) {
  while ((*str != symbol) && (*str != 0)) {
    ++str;
  }

  return ((*str == symbol) ? str : nullptr);
}

const char* Strrchr(const char* str, char symbol) {
  const char* ptr = nullptr;
  while (*str != 0) {
    if (*str == symbol) {
      ptr = str;
    }

    ++str;
  }

  return ((symbol == '\0') ? str : ptr);
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest != 0) {
    const char* curr = src;
    while (*curr != *dest && *curr != 0) {
      ++curr;
    }

    if (*curr == 0) {
      return count;
    }
    ++count;
    ++dest;
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = 0;
  while (*dest != 0) {
    const char* curr = src;
    while (*curr != *dest && *curr != 0) {
      ++curr;
    }

    if (*curr != 0) {
      return count;
    }
    ++count;
    ++dest;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  while (*dest != 0) {
    const char* curr = breakset;
    while (*curr != *dest && *curr != 0) {
      ++curr;
    }

    if (*curr != 0) {
      return dest;
    }
    ++dest;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  int str_len = Strlen(str);
  int pat_len = Strlen(pattern);

  for (int i = 0; i <= str_len - pat_len; ++i) {
    int j = 0;

    while ((j < pat_len) && (str[i + j] == pattern[j])) {
      ++j;
    }

    if (j == pat_len) {
      return &str[i];
    }
  }

  return nullptr;
}