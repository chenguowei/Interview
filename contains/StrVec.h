//
// Created by 陈国威 on 2018/5/1.
//

#ifndef INTERVIEW_STRVEC_H
#define INTERVIEW_STRVEC_H

#include <iostream>
#include <memory>
#include <string>

using namespace std;
// 类 vector 类内存分配策略的简化实现

class StrVec
{
 public:
  StrVec():
	  elements(nullptr), first_free(nullptr), cap(nullptr)
  {

  }

  // 移动构造函数
  StrVec(StrVec &&s) noexcept
  	: elements(s.elements), first_free(s.first_free), cap(s.cap)
  {
	//另 s 进入这一的状态---对其运行析构函数是安全的
	s.elements = s.first_free = s.cap = nullptr;
  }

  StrVec(const StrVec& );						//拷贝构造函数
  StrVec& operator=(const StrVec& );			//拷贝赋值运算符
  ~StrVec ();									//析构函数
  void push_back(const std::string &);			//拷贝元素
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string* begin() const { return elements; }
  std::string* end() const { return first_free; }
  pair<string*, string*> alloc_n_copy(const string* b, const string *e);

 private:
  static std::allocator<std::string> alloc;		// 分配元素
  // 被添加元素的函数所使用
  void chk_n_alloc()
  {
	if (size() == capacity())
	  reallocate();
  }
  void free();				//销毁元素并释放内存
  void reallocate();		//获得更多内存并拷贝已有元素
  std::string *elements;	//指向数组首元素的指针
  std::string *first_free;	//指向数组第一个空闲元素的指针
  std::string *cap;			//指向数组尾后位置的指针
};

#endif //INTERVIEW_STRVEC_H
