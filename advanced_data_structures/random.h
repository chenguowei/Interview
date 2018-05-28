//
// Created by 陈国威 on 2018/5/18.
//

#ifndef INTERVIEW_RANDOM_H
#define INTERVIEW_RANDOM_H

#include <stdint.h>

class Random
{
 private:
  uint32_t seed_;

 public:
  explicit Random(uint32_t s) : seed_(s & 0x7ffffffu)
  {
	// avoid bad seeds
	if (seed_ == 0 || seed_ == 2147483647L)
	  {
		seed_ = 1;
	  }
  }

  uint32_t Next()
  {
	static const uint32_t M = 2147483647L;	// 2^32 -1
	static const uint64_t A = 16807;

	uint64_t product = seed_ * A;

	seed_ = static_cast<uint32_t >((product >> 31) + (product &M));

	if (seed_ > M)
	  {
		seed_ -= M;
	  }

	return seed_;
  }

  uint32_t UniFrom(int n)
  {
	return (Next () % n);
  }

  bool OneIn()
  {
	return (Next () % n) == 0;
  }

  uint32_t  Skewed(int max_log)
  {
	return UniFrom (1 << UniFrom (max_log + 1));
  }
};

#endif //INTERVIEW_RANDOM_H
