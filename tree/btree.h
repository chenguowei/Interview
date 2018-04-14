//
// Created by 陈国威 on 2018/4/3.
//

// 实现对 order 序(阶)的 B-TREE结构基本操作的封装
// 查找：search;	插入: insert;	删除:remove
// 创建：create;	销毁: destroy;	打印:print

#ifndef INTERVIEW_BTREE_H
#define INTERVIEW_BTREE_H

#include <iostream>
#include <stdbool.h>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

// 定义 m 阶 B 树的最小度数BTree_D = ceil(m)
// 在这里定义每个节点中关键字的最大数目为：2 * BTree_D -1, 即阶为：2* BTree_D


#define BTree_D        2
#define ORDER        (BTree_D * 2)  //定义为4阶B-tree, 2-3-4树。最简单为 3阶 B-tree, 2-3树

typedef int keyType;
typedef struct BTNode {
  int keynum;                        // 结点中关键字的个数， keynum <= BTree_N(4)
  keyType key[ORDER - 1];                // 关键字向量为 key[0...keynum-1]
  struct BTNode *child[ORDER];        // 孩子指针向量为 child[0...keynum]
  bool isLeaf;
} BTNode;

typedef BTNode *BTree;        // 定义BTree

//给定数据集data, 创建BTree
void BTree_create (BTree *tree, const keyType *data, int length);

// 销毁BTree, 释放内存空间
void BTree_destroy (BTree *tree);

// 在BTree 中插入关键字key
void BTree_insert (BTree *tree, keyType key);

// 在BTree 中移除关键字 key
void BTree_remove (BTree *tree, keyType key);

// 深度遍历BTree打印各层结点信息
void BTree_print (const BTree *tree, int layer);


//在 BTree 中查找关键字 key,
// 成功时返回找到的节点的地址及 key 在其中的位置 *pos
// 失败时返回 NULL 及查找失败时扫描到的节点位置 *pos
BTNode *BTree_search (const BTree *tree, int key, int *pos);

#ifdef __cplusplus
}
#endif

#endif //INTERVIEW_BTREE_H
