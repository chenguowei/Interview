//
// Created by 陈国威 on 2018/5/17.
//

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




