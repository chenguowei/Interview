//
// Created by 陈国威 on 2018/5/9.
//

#include "uthread.h"
#include <stdio.h>

void func1(void *arg)
{
  puts ("1");
  puts ("11");
  puts ("111");
  puts ("1111");
}


void func2(void *arg)
{
  puts ("22");
  puts ("222");
  uthread_yield (*(schedule_t*)arg);
  puts ("22");
  puts ("222");
}


void func3(void *arg)
{
  puts ("3333");
  puts ("3333");
  uthread_yield (*(schedule_t*)arg);
  puts ("3333");
  puts ("3333");
}


void context_test()
{
  char stack[1024*128];
  ucontext_t uc1, ucmain;

  getcontext (&uc1);
  uc1.uc_stack.ss_sp = stack;
  uc1.uc_stack.ss_size = sizeof (stack);
  uc1.uc_stack.ss_flags = 0;
  uc1.uc_link = &ucmain;

  makecontext (&uc1, (void (*)(void))func1, 0);

  swapcontext (&ucmain, &uc1);
  puts ("ma")
}

