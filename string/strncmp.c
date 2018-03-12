//
// Created by 陈国威 on 2018/3/12.
//


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int strncmp(const char* s1, const char *s2, size_t n)
{
  assert ( (s1 != NULL) && (s2 != NULL));

  const unsigned char *u1 = (const unsigned char*)s1; // 为什么要转成这样尼？
  const unsigned char *u2 = (const unsigned char*)s2;
  unsigned char c1, c2;

  while (n > 0)
    {
      c1 = *u1++;
      c2 = *u2++;

      if (c1 == '\0' || c1 != c2)
        return c1 - c2;
      n--;
    }

  return c1 - c2;
}
