//
// Created by 陈国威 on 2018/3/12.
//
// 字符串末尾 要加 '\0', 否则输出错位结果

#include <stdlib.h>
#include <assert.h>
char *strncpy(char *strDes, const char *strSrc, unsigned int count)
{
   assert (strDes != NULL && strSrc != NULL);
   char *address = strDes;
   while ( (count--) && *strSrc != '\0')
      *strDes++ = *strSrc++;
   *strDes = '\0';

   return address;
}


