//
// Created by 陈国威 on 2018/3/20.
//

/*
 *  给定一个有序数组，数组元素排序，试将该数组转换为一棵平衡二叉树
 *
 *
 *  思路：
 *  	用递归。
 *  	平衡的定义，就是指二叉树的子树高度之差不能超过1
 *
 *		选择中间元素作为根节点并创建后，剩下的元素分为两部分，可以看作是数组。这样剩下的
 *	元素在根节点左边的作为左子树，右边的作为右子树
 * */
#include <iostream>

using namespace std;

struct Node
{
  int key;
  Node *left;
  Node *right;
};

Node* createNewNode(int item)
{
  Node *temp = new Node;
  temp->key = item;
  temp->right = temp->left = NULL;

  return temp;
}

struct Node* sortedArrayToBST(int arr[], int start, int end)
{
  if (start > end)
    return NULL;

  //
  int mid = start + (end - start) /2;
  struct Node* root = createNewNode (arr[mid]); // 创建一个新节点

  root->left = sortedArrayToBST (arr, start, mid -1);
  root->right = sortedArrayToBST (arr, mid+1, end);

  return root;
}

struct Node* sortedArrayToBST(int arr[], int n)
{
  return sortedArrayToBST (arr, 0, n -1);
}
