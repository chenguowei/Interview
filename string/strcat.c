//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *strcat(char *strDes, const char *strSrc)
{
  assert( (strDes!= NULL) && (strSrc != NULL));

  char *address = strDes;
  while (*strDes != '\0')
    strDes++;   // 跳到字符串的末尾

  while ( (*strDes++ = *strSrc++) != '\0')
    ;

  //*strDes = '\0'; // 这个不需要
  return address;
}

