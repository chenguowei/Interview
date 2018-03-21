//
// Created by 陈国威 on 2018/3/19.
//

#ifndef INTERVIEW_DFS_H
#define INTERVIEW_DFS_H

#include <iostream>
#include <stack>
#include "Graphlnk.h"

using namespace std;

template <class T, class E>
void DFS(Graphlnk<T, E>& G, const T& v, int judge) // 非递归算法，参数 judge用以区分递归和非递归
{
  cout << "-----------非递归算法被调用--------------" << endl;
  stack<int > s;
  int i, loc, out, next;
  int n = G.NumberOfVertices ();  // 顶点数
  bool *visited = new bool[n];
  for (i = 0; i < n; i++)
    visited[i] = false;

  loc = G.getVertexPos (v);
  s.push (loc);
  visited[loc] = true;  // 标记已读
  while (!s.empty ())
    {
      out = s.top ();
      s.pop ();
      cout << G.getValue (out) << " ";
      next = G.getFirstNeighbor (out);  // 将所有未被标记的邻接点压入栈中
      while (next != -1)
        {
          if (visited[next] == false)
            {
              s.push (next);
              visited[next] = true;
            }

          next= G.getNextNeighbor (out, next);  // 获取下一个邻接顶点
        }
    }
};

template <class T, class E>
void DFS(Graphlnk<T, E>& G, const T& v)
{
  cout << "-------------递归算法被调用----------------" << endl;
  int i, loc , n = G.NumberOfVertices ();
  bool *visited = new bool[n];
  for (i = 0; i < n; i++)
    visited[i] = false;

  loc = G.getVertexPos (v);
  DFS (G, loc, visited);

  delete[] visited;
};

template <class T, class E>
void DFS(Graphlnk<T, E>& G, int v, bool *visited) // 递归实现算法
{
  cout << G.getVertexPos (v) << " ";
  visited[v] = true;
  int w = G.getFirstNeighbor (v);
  while (w != -1)
    {
      if (visited[w] == false)
        {

          DFS (G, w, visited);
        }

      w = G.getNextNeighbor (v, w); // 获取下一个邻接表顶点
    }
};




#endif //INTERVIEW_DFS_H
