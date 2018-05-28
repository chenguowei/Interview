//
// Created by 陈国威 on 2018/4/18.
//

//
// Created by 陈国威 on 2018/4/18.
//

// 二项堆

#include <iostream>

typedef struct BinHeapNode BinNode;
typedef struct BinHeapNode *BinHeap;
typedef struct BinHeapNode *Position;

//节点ADT

struct BinHeapNode
{
  int key;
  int degree;	// 二项树的度数
  Position parent;
  Position leftChild;
  Position sibling;
};


// 用数组内的值建堆
BinHeap MakeBinHeapWithArray(int keys[], int n);

// 两个堆合并
BinHeap BinHeapUnion(BinHeap& H1, BinHeap& H2);

// 将H1,H2的根表合并成一个按度数的单调递增次序的链表
BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2);

// 使 H2 成为H1的父节点
void BinLink(BinHeap &H1, BinHeap &H2);

// 返回最小根节点的指针
BinHeap BinHeapMin(BinHeap heap);

//减少关键字的值
void BinHeapDecreaseKey(BinHeap heap, BinHeap x, int key);

//删除一个关键字
BinHeap BinHeapDelete(BinHeap &heap, int key);

// 找出一个关键字
BinHeap BinHeapFind(BinHeap heap, int key);

// 打印输出堆结构
void PrintBinHeap(BinHeap heap);

// 销毁堆
void DestroyBinHeap(BinHeap &heap);


// 用数组内的值建堆
BinHeap MakeBinHeapWithArray(int keys[], int n)
{
  BinHeap  heap = NULL, newHeap = NULL;
  for (int i = 0; i < n; ++i)
	{
	  newHeap = (BinHeap) malloc (sizeof (BinNode));
	  if (newHeap == NULL)
		{
		  puts ("Out of the Space");
		  exit (1);
		}
	  memset (newHeap, 0, sizeof (BinNode));
	  newHeap->key = keys[i];
	  if (NULL == heap)
		{
		  heap = newHeap;
		}
	  else
		{
		  heap = BinHeapUnion (heap, newHeap);
		  newHeap = NULL;
		}
	}

  return heap;
}


//两个堆合并
BinHeap BinHeapUnion(BinHeap &H1, BinHeap &H2)
{
  Position heap = NULL, pre_x = NULL, x = NULL, next_x = NULL;
  heap = BinHeapMerge (H1, H2);
  if (heap == NULL)
	{
	  return heap;
	}

  pre_x = NULL;
  x = heap;
  next_x = x->sibling;

  while (next_x != NULL)
	{
	  if ( (x->degree != next_x->degree) || //case 1 and case 2	当两个二项树的度数都不一样的时候，向前移动
		   ( (next_x->sibling != NULL) && (next_x->degree == next_x->sibling->degress)) )
		{
		  pre_x = x;
		  x = next_x;
		}
	  else if (x->key <= next_x->key)	// case3 当两个二项树的度数相同，且x的最小值小于 next_x的最小值
		{								// 则把 next_x 变为x 的某个子节点
		  x->sibling = next_x->sibling;
		  BinLink (next_x, x);
		}
	  else	// case 4			与3相反
		{
		  if (pre_x == NULL)
			{
			  heap = next_x;
			}
		  else
			{
			  pre_x->sibling = next_x;
			}
		  BinLink (x, next_x);
		  x = next_x;
		}
	  next_x = x->sibling;
	}

  return heap;
}


// 将H1, H2的根表合并成一个按度数的单调递增次序排列的链表
BinHeap BinHeapMerge(BinHeap &H1, BinHeap &H2)
{
  // heap->堆的首地址， H3指向新堆根结点
  BinHeap heap = NULL, firstHeap = NULL, secondHeap = NULL,
  		pre_H3 = NULL, H3 = NULL;

  if (H1 != NULL && H2 != NULL)
	{
	  firstHeap = H1;
	  secondHeap = H2;

	  //整个 while, firstHeap, secondHeap, pre_H3, H3都在向后顺移
	  while (firstHeap != NULL && secondHeap != NULL)
		{
		  if (firstHeap->degree <= secondHeap->degree)
			{
			  H3 = firstHeap;
			  firstHeap = firstHeap->sibling;
			}
		  else
			{
			  H3 = secondHeap;
			  secondHeap= secondHeap->sibling;
			}

		  if (pre_H3 == NULL)
			{
			  pre_H3 = H3;
			  heap = H3;
			}
		  else
			{
			  pre_H3->sibling = H3;
			  pre_H3 = H3;
			}

		  if (firstHeap != NULL)
			{
			  H3->sibling = firstHeap;
			}
		  else
			{
			  H3->sibling = secondHeap;
			}
		} // while
	}
  else if (H1 != NULL)
	{
	  heap = H1;
	}
  else
	{
	  heap = H2;
	}

  H1 = H2 = NULL;
  return heap;

}


// 使 H1 成为 H2 的父节点
void BinLink(BinHeap &H1, BinHeap &H2)
{
  H1->parent = H2;
  H1->sibling = H2->leftChild;
  H2->leftChild = H2;
  H2->degree++;
}


// 返回最小根结点的指针
BinHeap BinHeapMin(BinHeap heap)
{
  Position  y = NULL, x = heap;
  int min = INT_MAX;

  while (x != NULL)
	{
	  if (x->key <= min)
		{
		  min = x->key;
		  y = x;
		}
	  x = x->sibling;
	}

  return y;
}


// 抽取有最小关键字的结点
BinHeap BinHeapExtractMin(BinHeap &heap)
{
  BinHeap pre_y = NULL, y = NULL, x = heap;
  int min = INT_MAX;

  while (x != NULL)
	{
	  if (x->key < min)
		{
		  min = x->key;
		  pre_y = y;
		  y = x;
		}
	  x = x->sibling;
	}


  if (y == NULL)
	{
	  return NULL;
	}

  if (pre_y == NULL)
	{
	  heap = heap->sibling;
	}
  else
	{
	  pre_y->sibling = y->sibling;
	}

  // 将y的子节点指针 reverse
  BinHeap H2 = NULL, p = NULL;
  x = y->leftChild;
  while ( x != NULL)
	{
	  p = x;
	  x = x->sibling;
	  p->sibling = H2;
	  H2 = p;
	  p->parent = NULL;
	}

  heap = BinHeapUnion (heap, H2);
  return y;
}


// 减少关键字的值
void BinHeapDecreaseKey(BinHeap heap, BinHeap x, int key)
{
  if (key > x->key)
	{
	  puts ("new key is greate than current key");
	  exit (1);	// 不降键
	}
  x->key = key;

  BinHeap z = NULL, y = NULL;
  y = x;
  z = x->parent;
  while (z != NULL && z->key > y->key)
	{
	  swap(z->key, y->key);
	  y = z;
	  z = y->parent;
	}
}



// 删除一个关键字
BinHeap BinHeapDelete(BinHeap &heap, int key)
{
  BinHeap x = NULL;
  x = BinHeapFind (heap, key);
  if (x != NULL)
	{
	  BinHeapDecreaseKey (heap, x, INT_MIN);
	  return BinHeapExtractMin (heap);
	}

  return x;
}


// 找出一个关键字
BinHeap BinHeapFind(BinHeap &heap, int key)
{
  Position p = NULL, x = NULL;
  p = heap;

  while (p != NULL)
	{
	  if (p->key == key)
		{
		  return p;
		}
	  else	//先找这个二项树的子节点
		{
		  if ( (x = BinHeapFind (p->leftChild, key)) != NULL)
			{
			  return x;
			}
		}

	  p = p->sibling;
	}

  return NULL;
}


// 打印输出堆结构
void PrintBinHeap(BinHeap heap)
{
  if (NULL == heap)
	{
	  return;
	}
  Position  p = heap;

  while (p != NULL)
	{
	  printf (" (");
	  printf ("%d", p->key);
	  //显示子孩子
	  if (NULL != p->leftChild)
		{
		  PrintBinHeap (p->leftChild);
		}

	  printf (") ");
	  p = p->sibling;
	}

}

int kp1[8] = {12, 7, 25, 15, 28, 33, 41};
int kp2[20] = {18, 3, 37, 6, 8, 29, 10, 44, 30,
			23, 2, 48, 31, 17, 45, 32, 24, 50, 55};
int kp4[23] = {
	37, 41, 10, 28, 13, 77, 1, 6, 16, 12, 25, 8, 14,
	29, 26, 23, 18, 11, 17, 38, 42, 27
};

int main()
{
  BinHeap H1 =  NULL;
  H1 = MakeBinHeapWithArray (kp1, 7);
  puts ("第一个二叉堆 H1: ");
  PrintBinHeap (H1);

  BinHeap H2= NULL;
  H2 = MakeBinHeapWithArray (kp2, 19);
  puts ("第二个二叉堆H2: ");
  PrintBinHeap (H2);

  BinHeap H3 = NULL;
  H3 = BinHeapUnion (H1, H2);
  puts ("\n\n合并H1, H2，得到H3");

  BinHeap H4 = NULL;
  H4 = MakeBinHeapWithArray (kp4, 24);
  puts ("\n\n用于测试提取和删除的二叉堆H4");
  PrintBinHeap (H4);

  BinHeap extractNode = BinHeapExtractMin (H4);
  if (extractNode != NULL)
	{
	  printf ("\n\n抽取最小的值 %d 后：\n", extractNode->key);
	  PrintBinHeap (H4);
	}

  extractNode = BinHeapExtractMin (H4);
  if (extractNode != NULL)
	{
	  printf ("\n\n抽取最小的值 %d 后：\n", extractNode->key);
	  PrintBinHeap (H4);
	}

  extractNode = BinHeapExtractMin (H4);
  if (extractNode != NULL)
	{
	  printf ("\n\n抽取最小的值 %d 后：\n", extractNode->key);
	  PrintBinHeap (H4);
	}


  BinHeapDelete (H4, 12);
  puts ("\n\n删除12后: ");
  PrintBinHeap (H4);

  return 0;


}
