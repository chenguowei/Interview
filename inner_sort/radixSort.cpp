//
// Created by 陈国威 on 2018/4/18.
//

/*
 *  name: 基数排序
 * */

#include <iostream>

using namespace std;

/*
 *  打印数组
 * */

void printArray(int array[], int length)
{
  for (int i = 0; i < length; ++i)
	{
	  cout << array[i] << " ";
	}

  cout << endl;
}

/*
 *  求数据的最大位数，决定排序次数
 * */
int maxbit(int data[], int n)
{
  int d = 1;	// 保存最大的位数
  int p = 10;
  for (int i = 0; i < n; ++i)
	{
	  while (data[i] >= p)	// 不停地比较
		{
		  p *= 10;
		  ++d;
		}
	}

  return d;
}


/*
 *  基数排序的主干
 * */
void radixsort(int data[], int n)
{
  int d = maxbit (data, n);
  int tmp[n];
  int count[10];	// 计数器
  int i, j, k;
  int radix = 1;

  for (i = 1; i <= d; i++)	// 进行 d 次排序
	{
	  for (j = 0; j < 10; j++)
		count[j] = 0;	//每次分配前清空计数器

	  for (j = 0; j < n; j++)
		{
		  k = (data[j] / radix) % 10;	// 统计每个桶中的记录数
		  count[k]++;
		}

	  for (j = 1; j < 10; j++)
		count[j] = count[j] + count[j-1];	//将tmp中的位置一次分给每个桶

	  for (j = n -1; j >= 0; j--)	// 将桶中的记录依次放入到tmp数组中
		{
		  k = (data[j] / radix) % 10;
		  tmp[count[k] - 1] = data[j];
		  count[k]--;
		}

	  for (j = 0; j < n; j++)	// 将临时数组的内容复制到data数组中
		data[j] = tmp[j];

	  radix = radix * 10;
	}
}


int main()
{
  int array[] = {73, 22, 93, 43, 55, 14, 28, 76, 81};
  radixsort (array, 9);
  printArray (array, 9);

  return 0;
}

