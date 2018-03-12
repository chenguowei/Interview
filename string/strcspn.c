//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// 用来计算字符串 str 中连续有几个字符都不属于字符串 accept.
// 返回 字符串 str 开头连续不含字符串 accept 内的字符数目
int strcspn(const char *str, const char *accept)
{
  assert ( (str != NULL) && (accept != NULL));

  const char *s;
  const char *t = str;

  while (*t != '\0')
    {
      s = accept;
      while (s != '\0')
        {
          if (*s == *t)
            return *t - *str;
          ++s;
        }
      ++t;
    }

  return 0;

}

