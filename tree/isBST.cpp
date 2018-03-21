//
// Created by 陈国威 on 2018/3/20.
//
// 检查一个二叉树是否是一个棵二叉搜索树
// 二叉搜索树的定义：
// (1) 节点的左子树中的任意节点小于根节点
// (2) 节点的右子树中的任意节点大于根节点
// (3) 左右子树都必须是二叉查找树，不允许存在重复节点
//

#include <iostream>

using namespace std;


struct Node
{
  int key;
  Node *left;
  Node *right;
};


// 方法1 （结果正确，但是效率比较地）
// 对于每个节点，检测左子树中的最大值是否比它的小，而右子树的最小值都比它的大


// 返回一颗非空二叉树的最大值
int maxValue(Node* node)
{
  if (node == NULL)
    return 0;

  Node *p = node;
  while (p->right != NULL)
    p = p->right;

  return p->key;
}


// 返回一颗非空树中的最小值
int minValue(Node* node)
{
  if (node == NULL) // 其实这有点不严谨，如果 node.key 值可能为0的话，那就不好判断了。
    return 0;

  Node* p = node;
  while (p->left != NULL)
    p = p->left;

  return p->key;

}

// 如果是 BST, 则返回true
bool isBST1(Node* node)
{
  if (node == NULL)
    return true;

  // 如果左子树最大值大于根节点，则返回false
  if ( node->left != NULL && maxValue (node->left) > node->key)
    return false;

  // 如果右子树最小值小于根节点，则返回false
  if ( node->right != NULL && minValue (node->right) < node->key)
    return false;

  // 递归判断
  if (!isBST1 (node->left) && !isBST1 (node->right))
    return false;

  // 所有检测都通过，是BST
  return true;
}



/**
 * 方法2： 正确且有效率
 * 方法1因为要重复的遍历树中的部分数据，效率比较低。更好的方案是只遍历一次。方法2限定
 * 了子树中节点值的范围，从而每个节点只需访问一次。节点值的初始范围限定为 INT_MIN 以及
 * */

bool isBSTUtil(Node* node, int min, int max);

bool isBST2(Node *node)
{
  return (isBSTUtil (node, INT_MIN, INT_MAX));
}

// 如果是一颗二叉搜索树，且值范围在[min, max] ,则返回true
bool isBSTUtil(Node *node, int min, int max)
{
  // 空树也是BST
  if (node == NULL)
    return true;

  // 如果节点值违反了最大/最小约束条件，则不是BST
  if (node->key < min || node->key > max)
    return false;

  // 递归检查子树 ,加一或减一是因为不能存在重复值
  return isBSTUtil (node->left, min, node->key -1) && isBSTUtil (node->right, node->key + 1, max);
}


// 创建一个新的 BST 节点
Node* createNewNode(int item)
{
  Node *temp = new Node;
  temp->key = item;
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}



/**
 * 方法3：使用中序遍历
 *
 * (1) 对树进行中序遍历，将结果保存在temp数组中
 * (2) 检测temp数组中元素是否为升序排序，如果是，则这棵树为 BST
 * 时间复杂度为O(n)
 *
 * 可以保存一个前驱节点（或者它的值）
 *
 * */

bool isBST3(Node* root)
{
  static Node *prev = NULL;

  // 中序遍历这课树，并保存前驱节点至 prev 中
  if (root)
    {
      if (!isBST3 (root->left))
        return false;

      // 检测节点值的合法性
      if (prev != NULL && root->key <= prev->key)
        return false;

      prev = root;

      // 右子树
      return isBST3 (root->right);
    }

  return true;
}


int main(void)
{
  /* tree1
    4
   / \
  2   5
 /  \
 1   3

   */

  Node *root = createNewNode (4);
  root->left = createNewNode (2);
  root->right = createNewNode (5);
  root->left->left = createNewNode (1);
  root->left->right = createNewNode (3);

  if (isBST1 (root))
    std::cout << " tree1 is BST\n";
  else
    cout << "tree1 is not BST\n";

  return 0;

}



