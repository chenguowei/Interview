//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 比较 str1 和 str2 所指的内存区间前 count 个字符
int memcmp(const void *str1, const void *str2, size_t count)
{
  const unsigned char *s1 = str1; //强制转换为 char*
  const unsigned char *s2 = str2;

  while (count-- >  0)
    {
      if (*s1++ != *s2++)
        return s1[-1] < s2[-1] ? -1 : 1;  //比较当前字符的大小
    }

  return 0;
}

