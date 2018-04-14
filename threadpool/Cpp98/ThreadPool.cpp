//
// Created by 陈国威 on 2018/3/26.
//
#include "ThreadPool.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


namespace chen
{

	ThreadPool::ThreadPool (int threadNum)
	{
	  isRunning_ = true;
	  threadNums_ = threadNum;
	  createThread ();
	}

	ThreadPool::~ThreadPool ()
	{
	  stop ();
	  for (std::deque<Task*>::iterator it = taskQueue_.begin ();
		  it != taskQueue_.end (); it++)
		{
		  delete *it;
		}

	  taskQueue_.clear ();
	}

	int ThreadPool::createThread ()
	{
	  pthread_mutex_init (&mutex_, NULL);
	  pthread_cond_init (&condition_, NULL);
	  threads_ = (pthread_t*) malloc (sizeof (pthread_t) * threadNums_);
	  for (int i = 0; i < threadNums_; ++i)
		{
		  pthread_create (&threads_[i], NULL, threadFunc, this);
		}

	  return 0;
	}

	size_t ThreadPool::addTask (Task *task)
	{
	  pthread_mutex_lock (&mutex_);
	  taskQueue_.push_back (task);
	  int size = taskQueue_.size ();
	  pthread_mutex_unlock (&mutex_);
	  pthread_cond_signal (&condition_);
	}

	void ThreadPool::stop ()
	{
	  if (!isRunning_)
		{
		  return;
		}

	  isRunning_ = false;
	  pthread_cond_broadcast (&condition_);

	  for (int i = 0; i < threadNums_; ++i)
		{

		  pthread_join (threads_[i], NULL);
		}

	  free (threads_);
	  threads_ = NULL;

	  pthread_mutex_destroy (&mutex_);
	  pthread_cond_destroy (&condition_);
	}

	int ThreadPool::size ()
	{
	  pthread_mutex_lock (&mutex_);
	  int size = taskQueue_.size ();
	  pthread_mutex_unlock (&mutex_);

	  return size;
	}

	// 堵塞函数，
	Task* ThreadPool::take ()
	{
	  Task* task = NULL;
	  while (!task)
		{
		  pthread_mutex_lock (&mutex_);
		  while (taskQueue_.empty () && isRunning_)
			{
			  pthread_cond_wait (&condition_, &mutex_);
			}


		  if (!isRunning_)
			{
			  pthread_mutex_unlock (&mutex_);
			  break;
			}
		  else if (taskQueue_.empty ())
			{
			  pthread_mutex_unlock (&mutex_);
			  continue;
			}

		  assert (!taskQueue_.empty ());
		  task = taskQueue_.front ();
		  taskQueue_.pop_front ();
		  pthread_mutex_unlock (&mutex_);
		}

	  return task;
	}

	// 执行该函数，每次从工作队列中取出一个工作来运行
	void* ThreadPool::threadFunc (void *threadData)
	{
	  pthread_t tid = pthread_self ();
	  ThreadPool* pool = static_cast<ThreadPool*>(threadData);
	  while (pool->isRunning_)
		{
		  Task* task = pool->take ();
		  if (!task)
			{
			  printf ("thread %lu will exit\n", tid);
			  break;
			}

		  assert (task);
		  task->run ();
		}

	  return 0;
	}
}

