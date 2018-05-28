//
// Created by 陈国威 on 2018/5/9.
//

#ifndef INTERVIEW_UTHREAD_H
#define INTERVIEW_UTHREAD_H

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include <ucontext.h>
#include <vector>

#define DEFAULT_STACK_SIZE (1024*128)
#define MAX_UTHREAD_SIZE 1024

enum ThreadState
{
  FREE,
  RUNNABLE,
  RUNNING,
  SUSPEND
};

struct schedule_t;

typedef void (*Fun)(void *arg);

typedef struct uthread_t
{
  ucontext_t ctx;
  Fun func;
  void *arg;
  enum  ThreadState state;
  char stack[DEFAULT_STACK_SIZE];
} uthread_t;


typedef struct schedule_t
{
  ucontext_t main;
  int running_thread;
  uthread_t *threads;
  int max_index;	//

  schedule_t(): running_thread(-1), max_index(0)
  {
	threads = new uthread_t[MAX_UTHREAD_SIZE];
	for (int i = 0; i < MAX_UTHREAD_SIZE; ++i)
	  {
		threads[i].state = FREE;
	  }
  }

  ~schedule_t ()
  {
	delete[] threads;
  }
}schedule_t;


static void uthread_body(schedule_t *ps);

//create a user's thread
int uthread_create(schedule_t &schedule, Fun, void *arg);

// Hang thre currently running thread, switch to main thread
void uthread_yield(schedule_t &schedule);

// resume the thread which index equal id
void uthread_resume(schedule_t &schedule, int id);

/*
 * 测试是否所有的线程跑完了
 *
 * return 1 if all thread run over , otherwise return 0
 * */
int schedule_finished(const schedule_t &schedule);



#endif //INTERVIEW_UTHREAD_H
