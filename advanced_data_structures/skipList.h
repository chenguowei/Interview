//
// Created by 陈国威 on 2018/5/17.
//
#include <stddef.h>
#include "random.h"

// 定义调试开关
#define Debug

// 最大层数
const int MAX_LEVEL = 16;

// 定义 key 和 value 的类型
typedef int keyType;
typedef int valueType;

// 定义结点
typedef struct nodeStructure *Node;
struct nodeStructure
{
  keyType key;
  valueType value;
  Node forward[1];
};

// 定义跳跃表
typedef struct listStructure *List;
struct listStructure
{
  int level;
  Node header;
};


class SkipList
{
 public:
  // 初始化表结构
  SkipList() : rnd_(0xdeafbeef)
  { NewList (); }

  // 释放内存空间
  ~SkipList ()
  { FreeList (); }

  // 搜索key, 保存结果至value
  // 找到，返回true
  // 未找到，返回 false
  bool Search(const keyType& key, valueType& value);

  // 插入key 和 value
  bool Insert(const keyType& key, const valueType& value);

  // 删除 key, 保存结果至 value
  // 删除成功返回true
  // 未删除成功返回 false
  bool Delete(const keyType& key, valueType& value);

  // 链表包含元素的数目
  int size()
  { return size_; }

  // 打印当前最大的 level
  int GetCurrentLevel();

 private:
  //初始化表
  void NewList();

  // 释放表
  void FreeList();

  // 创建一个新的结点，结点的层数为 level
  void NewNodeWithLevel(const int& level, Node& node);

  // 随机生成一个level
  int RandomLevel();
 private:
  List list_;
  Node NIL_;
  // 链表中包含元素的数目
  size_t size_;
  // 随机生成器
  Random rnd_;
};




