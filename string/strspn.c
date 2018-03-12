//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 用来计算字符串 str 中连续有几个字符都属于字符串 accept,
// 返回 字符串 str 开头连续包含字符串 accept 内的字符数目

int strspn(const char *str, const char *accept)
{
  assert ( (str!= NULL) && (accept != NULL));

  const char *s;
  const char *t = str;

  while (*t != '\0')
    {
      s = accept;
      while (*s != '\0')
        {
          if (*t == *s)
            break;
          s++;
        }
      if (*s == '\0') // 在 accept中没有搜索到 *t
        return *t - *str;
      t++;
    }

  return 0;
}

