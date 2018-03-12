//
// Created by 陈国威 on 2018/3/6.
// 1000w 数据量，要保证生成不重复的数据量，一般的程序没有做到
//

#include <iostream>
#include <time.h>
#include <assert.h>

using namespace std;

const int size = 10000000;
int num[size];

int main()
{
  int n;
  FILE *fp = fopen ("data.txt", "w");
  assert (fp);

  for (n = 1; n < size; n++)
    num[n] = n;
  srand ((unsigned) time (NULL));
  int i, j;

  for (n = 0; n < size; n++)
    {
      i = (rand () * RAND_MAX + rand ()) * 10000000;
      j = (rand () * RAND_MAX + rand ()) * 10000000;
      swap (num[i], num[j]);
    }


  for (n = 0; n < size; n++)
    fprintf (fp, "%d", num[n]);

  fclose (fp);
  return 0;
}

