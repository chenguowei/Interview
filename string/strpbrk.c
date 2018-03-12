//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 返回两个字符串首个相同字符的位置
char *strpbrk(const char *strSrc, const char *str)
{
  assert ( (strSrc != NULL) && (str != NULL));

  const char *p;

  while (*strSrc != '\0')
    {
      for (p = str; *p ; ++p)
        {
          if (*strSrc == *p)
            return (char *)strSrc;
         strSrc++;
        }
    }

  return 0;

}

