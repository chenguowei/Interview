//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// 复制 src 所指的内存内容的前 len 个字节到 dest 所指的内存地址上
// dest 指针要分配足够的空间，。如果没有分配空间，会出现段错误
// dest 和 src 所指的内存空间不能重叠 （如果发生了重叠，使用 memmove() 会更加安全）
void *memcpy(void *dest, const void *src, size_t len)
{

  assert ( (dest != NULL) && (src != NULL));

  char *d = dest;
  const char *s = src;

  while (len--)
    *d++ = *s++;

  return dest;
}

