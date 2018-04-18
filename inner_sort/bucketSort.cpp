//
// Created by 陈国威 on 2018/4/18.
//

/*
 *  桶排序：时间复杂度为 O(n) 的排序方法，需要的空间复杂度跟被排序的最大值和最小值有关
 * */

#include <vector>
#include <iostream>

using namespace std;

void bucketSort(vector<int>& vec)
{
  int length = vec.size ();
  vector<int > buckets(length, 0);  // 准备一堆桶

  for (int i = 0; i < length; ++i)
    {
      buckets[vec[i]]++;  // 把每个蛋放入到对应的桶中
    }

  int index = 0;
  for (int j = 0; j < length; ++j)
    {
      // 把蛋取出，空桶则直接跳过
      for (int i = 0; i < buckets[i]; ++i)
        {
          vec[index++] = i;
        }
    }
}

// 感觉这排序跟计数排序差不多了
int main()
{
  int a[10] = {0, 2, 5, 6, 3, 2, 5, 9,5, 2};
  vector<int> vec(a, a+10);

  bucketSort (vec);

  for (int i = 0; i < vec.size (); ++i)
    {
      cout << vec[i] << " ";
    }


  return 0;
}

