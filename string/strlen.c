//
// Created by 陈国威 on 2018/3/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define _SIZE_TYPE long unsigned int

_SIZE_TYPE strlen(const char *str)
{
  assert ( str != NULL);
  _SIZE_TYPE i = 0;

  while (*str != '\0')
    i++;

  return i;
}

