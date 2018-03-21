//
// Created by 陈国威 on 2018/3/19.
//

#ifndef INTERVIEW_GRAPH_H
#define INTERVIEW_GRAPH_H

#include <iostream>

using namespace std;

#define	INF	100000	// 表示正无穷

const int DefaultVertices = 30;

template<class T, class E>
class Graph
{
 public:
  static const E maxWeight = INF;
  Graph(int size = DefaultVertices){};
  ~Graph ();
  bool GraphEmpty() const 	// 检查是否为空
  {
	if (numVertices == 0)
	  return true;
	else
	  return false;
  }

  bool GraphFull() const // 检查是否为满
  {
	if (numVertices == maxVertices || numEdges == maxVertices*(maxVertices-1)/2)
	  return true;
	else
	  return false;
  }

  int NumberOfVertices() const 	// 返回当前顶点数
  {
	return numVertices;
  }

  int NumberOfEdges() const 	// 返回当前边数
  {
	return numEdges;
  }
 protected:
  int maxVertices;	// 最大顶点数
  int numEdges;		// 边数
  int numVertices;	// 实际的顶点数
};

#endif //INTERVIEW_GRAPH_H
