//
// Created by 陈国威 on 2018/3/8.
//


#include <stdlib.h>
#include <time.h>
#include <algorithm>

/*
 * 快速排序最理想的情况就是每次都可以划分为相等的两个子序列
 *
 * */

void swap(int *a, int *b)
{
  int c;
  c = *a;
  *a = *b;
  *b = c;
}


/* 取序列的第一个或最后一个元素作为基准 */
int SelectPivot(int arr[], int low, int high)
{
  return arr[low];
}


/* 随机选择枢轴的位置，区间在 low 和high之间 */
int SelectPivotRandom(int arr[], int low, int high)
{
  // 产生枢轴的位置
  srand ((unsigned)time(NULL));
  int pivotPos = rand () % (high - low) + low;

  //把枢轴位置的元素和 low 位置元素交换，此时可以和普通的快排一样调用划分函数
  swap (&arr[pivotPos], &arr[low]);
  return arr[low];
}


/* 三数取中 */
/* 函数作用，取待排序序列中 low. mid. high 三个位置上数据，选取他们中间的那个数据作为枢轴 */
int SelectPivotMedianOfThree(int arr[], int low, int high)
{
  int mid = low + ((high - low) >> 1);		//计算数组中间元素的下标

  // 使用三数取中法选择枢轴
  if (arr[mid] > arr[high])		//目标： arr[mid] <= arr[high]
	{
	  swap (&arr[mid], &arr[high]);
	}
  if (arr[low] > arr[high])		//目标： arr[low] <= arr[high]
	{
	  swap (&arr[low], &arr[high]);
	}
  if (arr[mid] > arr[low])		//目标： arr[low] >= arr[mid]
	{
	  swap (&arr[mid], &arr[low]);
	}

  // 此时, arr[mid] <= arr[low] <= arr[high]
  return arr[low];
  // low 位置上保存这三个位置中间的值，
  // 分割可以直接使用low位置的元素作为枢轴，而不用改变分割函数
}


/*
 *  在一次分割后，可以把与key元素相等的元素聚在一起，继续下次分割时，不用再对与 key 相等元素分割
 * */
void QSort(int arr[], int low, int high)
{
  int first = low;
  int last = high;

  int left = low;
  int right = high;

  int leftLen = 0;
  int rightLen = 0;

  if (high - low + 1 < 2)
	{
	  //采用插入算法
	  return;
	}

  // 一次分割
  int key = SelectPivotMedianOfThree (arr, low, high);	//使用三数中法选择枢轴

  while (low < high)
	{
	  while (high > low && arr[high] >= key)
		{
		  if (arr[high] == key && high != right)
			{
			  swap (&arr[right], &arr[high]);
			  right--;
			  rightLen++;
			}
		  high--;
		}

	  arr[low] = arr[high];
	  while (high > low && arr[low] <= key)
		{
		  if (arr[low] == key && left != low)
			{
			  swap (&arr[left], &arr[low]);
			  left++;
			  leftLen++;
			}
		  low++;
		}

	  arr[high] = arr[low];
	}
  arr[low] = key;

  // 一次快排结束
  // 把与枢轴key相同的元素移到枢轴最终位置周围
  int i = low - 1;
  int j = first;
  while (j < left && arr[i] != key)
	{
	  swap (&arr[i], &arr[j]);
	  j++;
	  i--;
	}

  i = low + 1;
  j = last;
  while (j > right && arr[i] != key)
	{
	  swap (&arr[i], &arr[j]);
	  i++;
	  j--;
	}

  QSort (arr, first, low - 1-leftLen);
  QSort (arr, low+1+rightLen, last);
}

void showArr(int arr[], int len)
{
  for (int i = 0; i < len; ++i)
	{
	  printf ("%d ", arr[i]);
	}
  printf ("\n");
}

int main(int argc, char **argv)
{
  int a[] = {43, 12, 89, 43, 78};

  showArr (a, 5);

  QSort (a, 0, 4);

  showArr (a, 5);

  printf ("\n");

  return 0;
}

