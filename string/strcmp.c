//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 比较两个字符串的大小
int strcmp(const char *s1, const char *s2)
{
  assert (s1 != NULL && s2 != NULL);

  while (*s1 && *s2 && *s1 == *s2)
    {
      s1++;
      s2++;
    }

  return (*s1 - *s2);
}

