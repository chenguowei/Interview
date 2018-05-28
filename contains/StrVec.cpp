//
// Created by 陈国威 on 2018/5/1.
//
#include "StrVec.h"

void StrVec::push_back (const std::string &s)
{
  chk_n_alloc ();	// 确保有空间容纳新的元素
  // 在first_free 指向的元素中构造 s 的副本
  alloc.construct (first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy (const string *b, const string *e)
{
  // 分配空间保存给定范围中的元素
  auto data = alloc.allocate (e - b);
  // 初始化并返回一个pair, 该pari由data 和 uninitialized_copy的返回值构成
  return {data, uninitialized_copy (b, e, data)};
}

void StrVec::free ()
{
  // 不能传递给 deallocate 一个空指针，如果 elements 为0，函数什么也不做
  if (elements)
    {
      // 逆序销毁元素
      for (auto p = first_free; p != elements; )
        alloc.destroy (p--);
      alloc.deallocate (elements, cap - elements);
    }
}

//拷贝控制成员
StrVec::StrVec (const StrVec &s)
{
  // 调用 alloc_n_copy 分配空间一容纳与s中一样多的元素（不回额外分配多的空间）
  auto newdata = alloc_n_copy (s.begin (), s.end ());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec ()
{
  free ();
}

// 拷贝赋值运算符
StrVec& StrVec::operator= (const StrVec &rhs)
{
  // 调用 alloc_n_copy 分配内存，大小与rhs中元素占用空间一样多
  auto data = alloc_n_copy (rhs.begin (), rhs.end ());
  free ();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::reallocate ()
{
  // 我们将分配当前大小两倍的内存空间
  auto newcapacity = size () ? 2*size () : 1;
  // 分配新的内存
  auto newdata = alloc.allocate (newcapacity);
  // 将数据从旧内存移动到新内存
  auto dest = newdata;  // 指向新数组中下一个空闲位置
  auto elem = elements; // 指向旧数组中下一个元素
  for (size_t i = 0; i != size (); i++)
    alloc.construct (dest++, std::move (*elem++));
  free ();  // 一旦我们移动完成元素就释放旧内存空间
  // 更新我们的数据结构，执行新元素
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}


