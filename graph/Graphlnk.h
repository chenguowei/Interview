//
// Created by 陈国威 on 2018/3/19.
//

#ifndef INTERVIEW_GRAPHLNK_H
#define INTERVIEW_GRAPHLNK_H

#include "Graph.h"


/*
 *  基于邻接表来实现图 (无向图)
 * */

template<class T, class E>
struct Edge		// 边界点的定义
{
  int dest;		// 边的另一顶点位置
  E	cost;		// 权值
  Edge(){};
  Edge<T, E>	*link;	// 下一条边链指针
  Edge(int num, E weight) : dest(num), cost(weight), link(NULL) {}	// 构造函数
  bool operator != (Edge<T, E>& R) const // 判断边不等否
  {
	return (dest!=R.dest) ? true:false;
  }
};

template <class T, class E>
struct Vertex
{
  T	data;	// 顶点名字
  Edge<T, E> *adj;	// 边链表的头指针
};


template <class T, class E>
class Graphlnk : public Graph<T, E>
{
 public:
  Graphlnk(int size = DefaultVertices);
  ~Graphlnk ();
  T getValue(int i)	// 返回某个顶点的值
  {
	return (i >= 0 && i < numVertices)?NodeTable[i].data: 0;
  }

  E getWeight(int v1, int v2);
  int getFirstNeighbor(int v);
  int getNextNeighbor(int v, int w);
  bool insertVertex(const T& vertex);
  bool insertEdge(int v1, int v2, E cost);
  bool removeVertex(int v);
  bool removeEdge(int v1, int v2);
  void inputGraph();
  void outputGraph();
  int getVertexPos(T vertex)
  {
	for (int i = 0; i < numVertices; ++i)
	  {
		if (NodeTable[i].data == vertex)
		  return i;
	  }
	return -1;	// 找不到则返回-1
  }

 private:
  Vertex<T, E>*	NodeTable;	// 顶点表
};

template <class T, class E>
Graphlnk::Graphlnk (int size)
{
  maxVertices = size;
  numVertices = 0;
  numEdges = 0;
  NodeTable = new Vertex<T, E>[maxVertices];
  if (NodeTable == NULL)
	{
	  cerr << "存储分配错！" << endl;
	  exit (-1);
	}
  for (int i = 0; i < maxVertices; ++i)
	{
	  NodeTable[i].adj = NULL;
	}
}

template <class T, class E>
Graphlnk::~Graphlnk ()	// 析构函数
{
  for (int i = 0; i < numVertices; ++i)
	{
	  Edge<T, E> *p = NodeTable[i].adj;
	  while (p != NULL)
		{	// 头删除法
		  NodeTable[i].adj = p->link;
		  delete p;
		  p = NodeTable[i].adj;
		}
	}

  delete [] NodeTable;
}

template <class T, class E>
E Graphlnk<T, E>::getWeight (int v1, int v2)	//返回边（v1, v2）的权重，边不存在则返回0
{
  if (v1 != -1 && v2 != -1)
	{
	  Edge<T, E> *p = NodeTable[v1].adj;	// 找到某个顶点的临接表头
	  while ( p!= NULL && p->dest != v2)
		p = p->link;
	  if (p != NULL)
		return p->cost;
	}

  return 0;
}

template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor (int v)	// 获得v的第一个邻接顶点，找不到则返回-1；
{
  if (v != -1 && v < numVertices)
	{
	  Edge<T, E> *p = NodeTable[v].adj;
	  if ( p != NULL)
		return p->dest;
	}

  return -1;
}

template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor (int v, int w)	// 获得v的邻接顶点w的下一邻接顶点
{
  if ( v < 0 || v >= numVertices|| w < 0 || w >= numVertices)
	return -1;

  Edge<T, E> *p = NodeTable[v].adj;
  while ( p != NULL && p->dest != w)
	p = p->link;
  if ( p!= NULL && p->link != NULL)
	return p->link->dest;

  return -1;
}

template <class T, class E>
bool Graphlnk<T, E>::insertVertex (const T &vertex)	// 插入点
{
  if (numVertices == maxVertices)
	return false;	// 图已满，插入失败
  NodeTable[numVertices].data = vertex;
  numVertices++;
  return true;
}


template <class T, class E>
bool Graphlnk<T, E>::removeVertex (int v)	// 删除点
{
  return false;
}

template <class T, class E>
bool Graphlnk<T, E>::insertEdge (int v1, int v2, E cost)	// 插入一条边，若边已存在，或参数不合理，返回false
{
  if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
	  Edge<T, E> *q, *p = NodeTable[v1].data;
	  // 先检查该边是否已经存在
	  while ( p!= NULL && p->dest != v2)
		p = p->link;
	  if ( p != NULL) // 找到该边
		{
		  cerr << "该边已存在，插入失败！" << endl;
		  return false;
		}

	  p = new Edge<T, E>();
	  q = new Edge<T, E>();

	  p->dest = v2;
	  p->cost = cost;
	  p->link = NodeTable[v1].adj;
	  NodeTable[v1].adj = p;	// 插入到邻接表表头

	  q->dest = v1;
	  q->cost = cost;
	  q->link = NodeTable[v2].adj;
	  NodeTable[v2].adj = q;
	  numEdges++;
	  return true;
	}

  return false;

}
#endif //INTERVIEW_GRAPHLNK_H
