//
// Created by 陈国威 on 2018/4/29.
//

#include <array>
#include <iostream>
#include <string>

template <typename T>
void print_array(T &arr)
{
  for (const auto &s : arr)
	std::cout << s << " ";
  std::cout << "\n";
}

int main(void)
{
  // 用聚合初始化构造
  std::array<int, 3> a1{ {1, 2, 3} };
  std::array<int, 3> a2 = {3, 2, 1};
  std::array<std::string, 2> a3 = { std::string("a"), "b"};

  // 支持容器操作
  std::sort (a1.begin (), a1.end ());
  std::reverse_copy (a2.begin (), a2.end (),
          std::ostream_iterator<int>(std::cout, " "));

  std::cout << "\n";

  std::array<char, 40> a;

  strcpy (a.data (), "Hello !World");

  printf ("%s\n", a.data ());

  print_array (a1);
  print_array (a2);
  std::cout << "\n" << a3.max_size ();
  std::cout << "\n";
  return 0;
}

