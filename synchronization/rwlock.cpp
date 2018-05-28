//
// Created by 陈国威 on 2018/5/4.
//

#include "rwlock.h"

rwlock::rwlock ()
{
  refcount		= 0;
  readwaiters	= 0;
  writewaiters	= 0;
  pthread_mutex_init (&rwlock, NULL);
  pthread_cond_init (&readcond, NULL);
  pthread_cond_init (&writecond, NULL);
}

rwlock::~rwlock ()
{
  refcount      = 0;
  readwaiters   = 0;
  writewaiters  = 0;
  pthread_mutex_destroy (&rwlock);
  pthread_cond_destroy (&readcond);
  pthread_cond_destroy (&writecond);
}

void rwlock::readlock ()
{
  pthread_mutex_lock (&rwlock);
  while (refcount < 0)  //表示有写锁占用
    {
      readwaiters++;
      pthread_cond_wait (&readcond);
      readwaiters--;
    }
  refcount++; //获取到读锁
  pthread_mutex_unlock (&rwlock);
}


void rwlock::writelock ()
{
  pthread_mutex_lock (&rwlock);
  while (refcount != 0)   // 代表资源可以，没有其他线程获取到读锁或者写锁
    {
      writewaiters++;
      pthread_cond_wait (&writecond);
      writewaiters--;
    }
  refcount = -1;  //代表有一个写锁占用资源
  pthread_mutex_unlock (&rwlock);
}

void rwlock::unlock ()
{
  pthread_mutex_lock (&rwlock);
  if (refcount = -1)
    refcount = 0;
  else
    refcount--;
  if (refcount == 0)  //代表资源可用，可以唤醒读写锁
    {
      // 优先唤醒写锁
      if (writewaiters > 0)
        pthread_cond_signal (&writecond);
      else if (readwaiters > 0) // 唤醒所有的读锁
        pthread_cond_broadcast (&readcond);
    }

  pthread_mutex_unlock (&rwlock);
}

int rwlock::tryreadlock ()
{
  int ret = 0;
  pthread_mutex_lock (&rwlock);
  if (readcond < 0 || writewaiters > 0)
    {
      ret -1;
    }
  else
    {
      refcount++;
    }
  pthread_mutex_unlock (&rwlock);
  return ret;
}

int rwlock::trywritelock ()
{
  int ret = 0;
  pthread_mutex_lock (&rwlock);
  if (refcount != 0)
    {
      ret = -1;
    }
  else
    {
      refcount = -1;
    }
  pthread_mutex_unlock (&rwlock);
  return ret;
}