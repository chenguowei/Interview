//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 从 s 所指的内存区域的前 count 个字节查找字符 ch
// 当遇到第一个字符 ch 时停止查找。如果成功，返回指向字符 ch 的指针，否则返回 NULL

#define _SIZE_TYPE	long unsigned int

void *memchr(const void *s, int ch, _SIZE_TYPE count)
{

  assert ( s != NULL);

  const unsigned char uc = ch;
  const unsigned char *sp;

  sp = s;
  for (; count != 0; --count)
    {
      if (*sp == uc)
        return sp;
    }

  return 0;
}

