//
// Created by 陈国威 on 2018/5/4.
//
#include <pthread.h>

/*
 *  这样的缺点是读锁总是可以先获取到，这样会导致写锁很难获取到。
 *  因为这有可能导致数据不能及时更新，读取的数据是过去的
 * */
class rwlock
{
 public:
  rwlock():read_cnt(0)
  {
	pthread_mutex_init (&read_cnt, NULL);
	pthread_mutex_init (&write_mtx, NULL);
  }

  ~rwlock ()
  {
	pthread_mutex_destroy (&read_mtx);
	pthread_mutex_destroy (&write_mtx);
  }

  void readLock()
  {
	pthread_mutex_lock (&read_mtx);
	if (++read_cnt == 1)	// 第一个调用线程则锁住写锁
	  pthread_mutex_lock (&write_mtx);
	pthread_mutex_lock (&read_mtx);	//如果怎么实现，那怎么启到锁的作用啊（不需要锁住，因为只是读锁就是控制同步）
  }

  void readUnlock()
  {
	pthread_mutex_lock (&read_mtx);
	if (--read_cnt == 0)
	  pthread_mutex_unlock (&write_mtx);
	pthread_mutex_unlock (&read_mtx);
  }

  void writeLock()
  {
	pthread_mutex_lock (&write_mtx);
  }

  void writeUnlock()
  {
	pthread_mutex_unlock (&write_mtx);
  }

 private:
  pthread_mutex_t read_mtx;
  pthread_mutex_t write_mtx;
  int read_cnt;	//读锁个数
};

