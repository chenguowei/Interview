//
// Created by 陈国威 on 2018/3/12.
//

#include <stdio.h>
#include <ctype.h>

// crytTable[] 里面保存的是 HashString 函数里面将会用到的一些数据，在 prepareCryptTable
// 函数里面初始化

unsigned long cryptTable[0x500];

// 以下的函数生成一个长度为 0x500 (含10进制：1280) 的 cryptTable[0x500]

void prepareCryptTable()
{
  unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

  for (index1 = 0; index1 < 0x100; ++index1)
	{
	  for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
		  unsigned long temp1, temp2;

		  seed = (seed * 125 + 3) % 0x2AAAAB;
		  temp1 = (seed & 0xFFFF) << 0x10;

		  seed = (seed * 125 + 3) % 0x2AAAAB;
		  temp2 = (seed & 0xFFFF);

		  cryptTable[index2] = (temp1 | temp2);
		}

	}
}

// 以下函数计算 lpszFileName 字符串的 hash 值，其中 dwHashType 为 hash 的类型
// 在下面 GetHashTablePos 函数里面调用本函数，其可以取的值 0 ，1，2；函数
// 返回 lpszFileName 字符串的 hash 值
unsigned long HashString(char *lpszFileName, unsigned long dwHashType)
{
  unsigned char *key = (unsigned char *)lpszFileName;
  unsigned long seed1 = 0x7FED7EFD;
  unsigned long seed2 = 0xEEEEEEEE;
  int ch;

  while (*key != 0)
	{
	  ch = toupper (*key++);

	  seed1 = cryptTable[(dwHashType << 8)] ^ (seed1 + seed2);
	  seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}

  return seed1;

}


