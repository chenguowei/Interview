//
// Created by 陈国威 on 2018/4/10.
//

#include "sort.h"

 /*
  * 插入排序： 将一个记录插入到已经排好序的有序表中，从而得到
  * 一个新的 ，记录增1的有序表
  * 时间复杂度为O(n^2), 比冒泡排序和选择排序的性能要更好一些
  * */

void InsertionSort(int arr[], int num)
 {
  int tmp;
 int j;
  for (int i = 1; i < num; ++i)
   {
      tmp = arr[i];
      for (j = i; j > 0 && arr[j-1] < tmp; --j)
       {
          arr[j] = arr[j-1];
       }
      arr[j] = tmp;
   }
 }