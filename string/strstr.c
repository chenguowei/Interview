//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <stdlib.h>
// 实现 strstr 函数，在字符串中查找指定字符串的第一次出现，不能找到则返回-1
// 找到则返回
char* strstr(const char *s1, const char* s2)
{
  const char *p, *q;

  for (; *s1; s1++)
    {
      p = s1, q = s2;
      while (*q && *p)
        {
          if (*q != *p)
            break;
          p++;
          q++;
        }

      if (*q == 0)  // 表示到达 s2 的 '\0' 字符
        return (char*)s1;
    }

  return 0;

}

int main(int argc, char **argv)
{
  if (argc != 3)
    {
      printf ("usage: strstr.c str1 str2\n");
      exit (-1);
    }

  printf (" str2 in str1 %s\n", strstr (argv[1], argv[2]));
  if (strstr (argv[1], argv[2]))
	printf ("in \n");
  else
    printf ("out \n");

  return 0;

}

