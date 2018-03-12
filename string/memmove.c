//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void *memmove(void *dest, const void *src, size_t len)
{
  assert ( (dest != NULL) && (src != NULL));

  char *d = dest;
  const char *s = src;

  if (d < s)  // dest 在 src 前面
    {
      while (len--)
        *d++ = *s++;
    }
  else
    { // 内存存在重叠， 则从后面开始复制
      char *lasts = s + (len - 1);
      char *lastd = d + (len - 1);
      while (len--)
        *lastd-- = *lasts--;
    }

  return dest;
}

