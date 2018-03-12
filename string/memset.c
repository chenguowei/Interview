//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void *memset(void *dest, int val, size_t len)
{
  assert ( dest != NULL);

  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = (char)val;

  return dest;
}

