//
// Created by 陈国威 on 2018/4/29.

//

#include <array>
#include <algorithm>
#include <functional>
#include <numeric>
#include "print.h"

using namespace std;

int main()
{
  // create array with 10 ints
  array<int, 10> a= {11, 22, 33, 44};

  print_elements (a);

  // modify last two elements
  a.back () = 99999;
  a[a.size () - 2] = 42;
  print_elements (a);

  cout << "sum: "
	   << accumulate (a.begin (), a.end (), 0)
       << endl;

  // negate all elements
  transform (a.begin (), a.end (),
            a.begin (), negate<int>());

  print_elements (a);

  return 0;
}

