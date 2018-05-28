//
// Created by 陈国威 on 2018/5/9.
//
#include "uthread.h"

// 启动某个
void uthread_resume(schedule_t &schedule, int fd)
{
  if (id < 0 || id > schedule.max_index)
    {
      return;
    }

  uthread_t* t = &(schedule.threads[fd]);

  if (t->state == SUSPEND)
    {
      swapcontext (&(schedule.max), &(t->ctx));
    }
}

void uthread_yield(schedule_t &schedule)
{
  if (schedule.running_thread != -1)
    {
      uthread_t* t = &(schedule.threads[schedule.running_thread]);
      t->state = SUSPEND;
      schedule.running_thread = -1;

      swapcontext (&(t->ctx), &(schedule.main));
    }
}

void uthread_body(schedule_t *ps)
{
  int id = ps->running_thread;

  if (id != -1)
    {
      uthread_t* t = ps->threads[id];

      t->func(t->arg);

      t->state = FREE;

      ps->running_thread = -1;
    }

}


int uthread_create(schedule_t& schedule, Fun func, void *arg)
{
  int id = 0;

  // 获取空闲的协程
  for (id = 0; id < schedule.max_index; ++id)
    {
      if (schedule.threads[id].state == FREE)
        {
          break;
        }
    }

  if (id == schedule.max_index)
    {
      schedule.max_index++;
    }
  // 获取创建好的协程
  uthread_t* t = &(schedule.threads[id]);

  t->state = RUNNABLE;
  t->func = func;
  t->arg = arg;

  // 保存当前的上下文
  getcontext (&(t->ctx));

  t->ctx.uc_stack.ss_sp = t->stack;
  t->ctx.uc_stack.ss_size = DEFAULT_STACK_SIZE;
  t->ctx.uc_stack.ss_flags = 0;
  t->ctx.uc_link = &(schedule.main);
  schedule.running_thread = id;

  makecontext(&(t->ctx), (void (*)(void))uthread_body, 1, &schedule);
  swapcontext (&(schedule.main), &(t->ctx));

  return id;

}

int schedule_finished(const schedule_t& schedule)
{
  if (schedule.running_thread != -1)
    {
      return 0;
    }
  else
    {
      for (int i = 0; i < schedule.max_index; ++i)
        {
          if (schedule.threads[i].state != FREE)
            {
              return 0;
            }
        }
    }
  return 1;
}



