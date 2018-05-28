//
// Created by 陈国威 on 2018/4/29.
//

#ifndef INTERVIEW_PRINT_H
#define INTERVIEW_PRINT_H
#include <iostream>

template <typename T>
void print_elements(const T& arrs)
{
  for (const auto& s : arrs)
    std::cout << s << " ";
  std::cout << "\n";
}

#endif //INTERVIEW_PRINT_H
