//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *strncat(char *strDes, const char *strSrc, unsigned int count)
{
  assert ( (strDes != NULL) && (strSrc != NULL));

  char *address = strDes;
  char c = '\0';
  while (*strDes != '\0')
    strDes++;


  while (count > 0)
    {
      c = *strSrc++;
      *strDes++ = c;
      if (c == '\0')
        return address;
      count--;
    }

  if (c != '\0')  // 就是没有复制strSrc 的 '\0' 字符
    *strDes = '\0';

  return address;

}

