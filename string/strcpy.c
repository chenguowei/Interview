//
// Created by 陈国威 on 2018/3/12.
//

#include <assert.h>
#include <stdlib.h>
// 考虑 源地址和目的地址有重叠的情况
char *strcpy(char *strDest, const char *strSrc)
{
  if (strDest == strSrc)
    return strDest;

  assert (strDest != NULL);
  assert (strSrc != NULL);

  char *r = strDest;  // 记录 目的地址的首地址
  while ( (*strDest++ = *strSrc++) != '\0')
    ;
  return r; // 返回目的地址的首地址
}

