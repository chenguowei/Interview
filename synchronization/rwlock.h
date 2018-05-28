//
// Created by 陈国威 on 2018/5/4.
//

#ifndef INTERVIEW_RELOCK_H
#define INTERVIEW_RELOCK_H
#include <pthread.h>
/*
 *  使用一个互斥量和两个条件变量来实现写锁优先
 * */
class rwlock {
  rwlock();
  ~rwlock ();
  void readlock();
  void writelock();
  void unlock();
  int tryreadlock();
  int trywritelock();

 private:
  pthread_mutex_t rwmutex;
  int refcount;		//-1表示写者，0表示没有加锁，正数表示有多少个读者
  int readwaiters;
  int writewaiters;
  pthread_cond_t readcond;
  pthread_cond_t writecond;
};

#endif //INTERVIEW_RELOCK_H
