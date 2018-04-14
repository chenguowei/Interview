//
// Created by 陈国威 on 2018/4/10.
//

/*
 * 冒泡排序时间复杂度最好的情况为 O(n),最坏为 O(n^2)
 * 基本思想是：两两比较相邻记录的关键字，如果反序则交换
 */

#include "sort.h"

void BubbleSort1(int arr[], int num)
{
  for (int i = 0; i < num; ++i)
	{
	  for (int j = 1; j < num -i; ++j)
		{
		  if (arr[j -1] > arr[j])
			swap1 (&arr[j-1], &arr[j]);
		}
	}
}



// 改进思路，设置标志位，明显如果有一趟没有发生交换
// flag = flase, 说明排序已经完成

void BubbleSort2(int arr[], int num)
{
  int k = num;
  int j;
  bool flag = true;
  while (flag)
	{
	  flag = false;
	  for (j = 1; j < k;j++)
		{
		  if (arr[j-1] > arr[j])
			{
			  swap1 (&arr[j-1], &arr[j]);
			  flag = true;
			}
		}
	  k--;
	}
}


// 改进思路：记录一轮下来标记的最后位置，下次从头遍历到这个位置就ok

void BubbleSort3(int arr[], int num)
{
  int k, j;
  int flag = num;
  while (flag > 0)
	{
	  k = flag;
	  flag = 0;
	  for (j = 1; j < k; j++)
		{
		  if (arr[j-1] > arr[j])
			{
			  swap1 (&arr[j-1], &arr[j]);
			  flag = j;
			}
		}
	}

}
