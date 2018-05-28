//
// Created by 陈国威 on 2018/5/9.
//

#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  ucontext_t context;

  getcontext(&context);
  puts ("Hello world ");
  sleep (1);
  setcontex(&context);
  return 0;
}

