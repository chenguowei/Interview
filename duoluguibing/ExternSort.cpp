//
// Created by 陈国威 on 2018/3/6.
//
//

#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

int sort_num = 10000000;
int memory_size = 250000;

// 每次只对 250 k个小数据量进行排序
int read_data(FILE* fp, int *space)
{
  int index = 0;
  while (index < memory_size && fscanf (fp, "%d", &space[index]) != EOF)
    index++;
  return index;
}

void write_data(FILE *fp, int *space, int num)
{
  int index = 0;
  while (index < num)
    {
      fprintf (fp, "%d", space[index]);
      index++;
    }
}

// check the file pointer whether valid or not
void check_fp(FILE *fp)
{
  if (fp == NULL)
    {
      cout << "The file pointer is invalid!" << endl;
      exit (1);
    }
}

int compare(const void *first_num, const void *second_num)
{
  return *(int *)first_num - *(int *)second_num;
}

string new_file_name(int n)
{
  char file_name[20];
  sprintf (file_name, "data%d.txt", n);
  return file_name;
}

int memory_sort()
{
  // open the target file.
  FILE *fp_in_file = fopen ("data.txt", "r");
  check_fp (fp_in_file);
  int counter = 0;
  while (true)
    {
      // allocate space to store data read from file.
      int *space = new int[memory_size];
      int num = read_data (fp_in_file, space);
      // the memory sort have finished if not numbers any more.
      if (num == 0)
        break;

      //quick sort
      qsort (space, num, sizeof (int), compare);
      // create a new auxiliary file name.
      string file_name = new_file_name (++counter);
      FILE *fp_aux_file = fopen (file_name.c_str (), "w");
      check_fp (fp_aux_file);

      // write the orderly numbers into auxiliary file.
      write_data (fp_aux_file, space, num);
      fclose (fp_aux_file);
      delete[] space;
    }

  fclose (fp_in_file);


  return counter;
}

void merge_sort(int file_num)
{
  if (file_num <= 0)
    return;

  // create a new file to store result
  FILE *fp_out_file = fopen ("result.txt", "w");
  check_fp (fp_out_file);

  // allocate a array to store the file pointer
  FILE **fp_array = new FILE*[file_num];
  int i;
  for (i = 0; i < file_num; i++)
    {
      string file_name = new_file_name (i + 1);
      fp_array[i] = fopen (file_name.c_str (), "r");
      check_fp (fp_array[i]);
    }

  int *first_data = new int[file_num];
  // new 出个大小为 0.1亿/250k 数组，由指针 first_data 指示数组首地址
  bool *finish = new bool[file_num];
  memset (finish, false, sizeof (bool) * file_num);

  // read the first number of every auxiliary file.
  for (i = 0; i < file_num; i++)
    fscanf (fp_array[i], "%d", &first_data[i]);

  while (true)
    {
      int index = 0;
      while (index < file_num && finish[index]) //?不懂这个有什么用
        index++;

      // the finish condition of the merge sort.
      if (index >= file_num)
        break;

      // 要保证所有文件都读完，必须使得 finish[0]..finish[40]都为真

      int min_data = first_data[index];
      // choose the relative minimun in the array of first_data.
      for (i = index + 1; i < file_num; i++)
        {
          if (min_data > first_data[i] && !finish[i])
            {
              min_data = first_data[i];
              i = index;
            }
        }

      // write the orderly result to file
      fprintf (fp_out_file, "%d", min_data);
      if (fscanf (fp_array[index], "%d", &first_data[index]) == EOF)  //再次读取最小数所在都文件
        finish[index] = true;
    }

  fclose (fp_out_file);
  delete [] finish;
  delete [] first_data;
  for (i = 0; i < file_num; i++)
    fclose (fp_array[i]);

  delete[] fp_array;

}



