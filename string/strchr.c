//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 查找字符串 s 中首次出现字符c的位置
char *strchr(const char *str, int c)
{
  assert (str != NULL);
  for (; *str != (char)c; str++)
    {
      if (*str == '\0')
        return NULL;
      else
        return str;
    }
}

