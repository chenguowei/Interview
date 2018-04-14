//
// Created by 陈国威 on 2018/3/26.
//

#ifndef INTERVIEW_THREADPOOL_H
#define INTERVIEW_THREADPOOL_H

#include <deque>
#include <string>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// 使用 C++98 语音规范实现的线程池：面向对象做法，每一个job都是Task继承的对象
namespace chen
{
	class Task
	{
	 public:
		Task(void *arg = NULL, const std::string taskName = "")
			: arg_(arg),
			taskname_(taskName)
				{

				}

	  virtual ~Task ()
	  {

	  }

	  void setArg(void* arg)
	  {
		arg_ = arg;
	  }

	  virtual int run() = 0;	// 定义为纯虚函数

	 private:
	  void*	arg_;
	  std::string taskname_;
	};


	class ThreadPool
	{

	 public:
	  ThreadPool(int threadNum = 10);
	  ~ThreadPool ();

	 public:
	  size_t addTask(Task* task);
	  void stop();
	  int 	size();
	  Task*	take();

	 private:
	  int createThread();
	  static void* threadFunc(void *threadData);

	 private:	//相当于禁止拷贝构造函数 和 复制函数
	  ThreadPool&	operator=(const ThreadPool&);
	  ThreadPool(const ThreadPool&);

	 private:
	  volatile bool			isRunning_;
	  int 					threadNums_;
	  pthread_t *			threads_;

	  std::deque<Task*>		taskQueue_;
	  pthread_mutex_t		mutex_;
	  pthread_cond_t		condition_;
	};
}

#endif //INTERVIEW_THREADPOOL_H
