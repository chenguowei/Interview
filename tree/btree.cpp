//
// Created by 陈国威 on 2018/4/4.
//

// B 树的实现
#include "btree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define cmp(a, b)  ( ((a)-(b) >= (0) )? (1):(0) )	//比较 a, b大小
#define DEBUG_BTREE


//模拟向磁盘写入节点
void disk_write(BTNode* node)
{
  // 打印出结点中的元素，方便调试查看keynum之后的元素是否为0（即是否存在垃圾数据）
  // 而不是 keynum 个元素
  printf ("向磁盘写入节点");
  for (int i = 0; i < ORDER-1; ++i)
    {
      printf ("%c", node->key[i]);
    }
  printf ("\n");
}


// 模拟从磁盘读取节点
void disk_read(BTNode** node)
{
  printf ("向磁盘读取节点");
  for (int i = 0; i < ORDER -1; ++i)
    {
      printf ("%c", (*node)->key[i]);
    }

  printf ("\n");
}

// 按层打印 B 树
void BTree_print(const BTree tree, int layer)
{
  int i;
  BTNode* node = tree;

  if (node)
    {
      printf ("第 %d 层， %d node: ", layer, node->keynum);

      // 打印出结点中的全部元素，方便调试查看keynum 之后的元素是否为0
      for (int j = 0; j < ORDER -1; ++j)
        {
          printf ("%c" , node->key[i]);
        }

      printf ("\n");

      ++layer;
      for (i = 0; i <= node->keynum; i++)
        {
          if (node->child[i])
            {
              BTree_print (node->child[i], layer);
            }
        }
    }
  else
    {
      printf ("树为空\n");
    }
}


// 结点node 内对关键字进行二分查找
int binarySearch(BTNode* node, int low, int high, keyType Fkey)
{
  int mid;
  while (low <= high)
    {
      mid = low + (high - low) / 2;
      if (Fkey < node->key[mid])
        {
          high = mid -1;
        }
      else if (Fkey > node->key[mid])
        {
          low = mid + 1;
        }
      else
        return mid; //   返回下标
    }

  return -1;   // 未找到返回0
}


/**********************************************
 * 将分裂的结点中的一半元素给新建的结点，并且将分裂结点中的中间关键字元素上移至父节点中
 * parent 是一个非满的父节点
 * node 是 tree 孩子表中下标为 index 的孩子结点，且是满的，需分裂
 */

void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
#ifdef DEBUG_BTREE
  printf ("BTree_split_child \n");
#endif

  assert (parent && node);
  int i;

  // 创建新节点，存储 node 中后半部分的数据
  BTNode* newNode = (BTNode*)calloc (sizeof (BTNode), 1);
  if (!newNode)
    {
      printf ("Error out of memory\n");
      return;
    }


  newNode->isLeaf = node->isLeaf;
  newNode->keynum = BTree_D -1;

  // 拷贝 node 后半部分关键字，然后将 node 后半部分置为0
  for (int j = 0; j < newNode->keynum; ++j)
    {
      newNode->key[i] = node->key[BTree_D+i];
      node->key[BTree_D + i] = 0;
    }


  // 如果 Node 不是叶子节点， 拷贝 node 后半部分的指向孩子节点的指针
  // 然后将 node 后半部分指向孩子节点的指针置为NULL
  if (!node->isLeaf)
    {
      for (i = 0; i < BTree_D; i++)
        {
          newNode->child[i] = node->child[BTree_D + i];
          node->child[BTree_D + i] = NULL;
        }
    }


  // 将 node 分裂出 newNode 之后，里面的数据减半
  node->keynum = BTree_D - 1;

  // 调整父节点中的指向孩子的指针和关键字元素。分裂时父节点增加指向孩子的指针和关键元素
  for (i = parent->keynum; i > index; --i)
    parent->child[i + 1] = parent->child[i];


  parent->child[index + 1] = newNode;

  // 将父节点的关键字向后移动一位，给 从孩子节点上移的元素空一个位置
  for (i = parent->keynum - 1; i >= index; --i)
    {
      parent->key[i + 1] = parent->key[i];
    }

  parent->key[index + 1] = node->key[BTree_D -1];
  ++parent->keynum;

  node->key[BTree_D - 1] = 0;

  // 写入磁盘
  disk_write (parent);
  disk_write (newNode);
  disk_write (node);
}


void BTree_insert_nonfull(BTNode* node, keyType key)
{
  assert (node);

  int i;


  // 节点是叶子节点，直接插入
  if (node->isLeaf)
    {
      i = node->keynum - 1;
      while (i >= 0 && key < node->key[i])  // 把节点的关键字后移
        {
          node->key[i + 1] = node->key[i];
          --i;
        }

      node->key[i + 1] = key;
      ++node->keynum;

      // 写入磁盘
    }


  // 节点是内部节点
  else
    {
      // 查找插入的位置
      i = node->keynum - 1;
      while (i > 0 && key < node->key[i])
        {
          --i;
        }

      ++i;

      // 从磁盘读取孩子节点
      disk_read (&node->child[i]);
    }


  // 如果该孩子节点已满，分裂调整值
  if (node->child[i]->keynum == (ORDER -1))
    {
      BTree_split_child (node, i, node->child[i]);
      // 如果待插入的关键字大于该分裂结点中上移到父节点的关键字，在该关键字的右孩子节点中进行插入操作
      if (key > node->key[i])
        {
          ++i;
        }
    }

  BTree_insert_nonfull (node->child[i], key);
}


void BTree_insert(BTree* tree, keyType key)
{
#ifdef DEBUG_BTREE
  printf ("BTree_insert\n");
#endif

  BTNode* node;
  BTNode* root = *tree;

  // 树为空
  if (NULL == root)
    {
      root = (BTNode*)calloc (sizeof (BTNode), 1);
      if (!root)
        {
          printf ("Error ! out of memory !\n");
          return;
        }

      root->isLeaf = true;
      root->keynum = 1;
      root->key[0] = key;

      *tree = root;

      // 写入磁盘
      disk_write (root);

      return;
    }

  // 根节点已满，插入前需要进行分裂调整
  if (root->keynum == (ORDER -1))
    {
      // 产生新节点当作根节点
      node = (BTNode*)calloc (sizeof (BTNode), 1);
      if (!node)
        {
          printf ("Error ! out of memory !\n");
          return;
        }

      *tree = node;
      node->isLeaf = false;
      node->keynum = 0;
      node->child[0] = root;

      BTree_split_child (node, 0, root);
      BTree_insert_nonfull (node, key);
    }

  // 根节点未满
  else
    {
      BTree_insert_nonfull (root, key);
    }
}



