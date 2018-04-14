//
// Created by 陈国威 on 2018/4/10.
//

#ifndef INTERVIEW_SORT_H
#define INTERVIEW_SORT_H

#include <iostream>

using namespace std;

/* 采用指针交换*/
void swap1(int *left, int *right)
{
  int temp = *left;
  *left = *right;
  *right = temp;
}

/* 采用 c++的引用 */
void swap2(int &left, int &right)
{
  int temp = left;
  left =right;
  right = temp;
}

/* 采用异或 */
void swap3(int &left, int &right)
{
  if (&left != &right)
    {
      left ^= right;
      right ^= left;
      left ^= right;
    }
}
#endif //INTERVIEW_SORT_H
