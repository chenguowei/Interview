//
// Created by 陈国威 on 2018/3/25.
//

// 增加一个 static 变量
#include <iostream>

using namespace std;

class Person
{
 public:
  Person(): mId(0), mAge(20)
  {
	++sCount;
  }


  virtual void print()
  {
	cout << "id: " << mId
		 << ", age: " << mAge << endl;
  }

  virtual void job()
  {
    cout << "Person" << endl;
  }

  ~Person ()
  {
	--sCount;
	cout << "~Persion " << endl;
  }

 private:
  static int sCount;
  int mId;
  int mAge;

};

int Person::sCount = 0;

typedef void (*FuncPtr)();

int main()
{
  Person persion;

//  cout << "sizeof(persion) == " << sizeof (persion) << endl;
//  int *p = (int*)&persion;
//  for (int i = 0; i < sizeof (persion)/ sizeof (int); ++i, ++p)
//	{
//	  cout << *p << endl;

  //虚函数表保存的是函数的指针，则把虚函数表当作一个数组
//  int **p = (int **)&persion;
//  int **vtb1 = (int **)*p;	//虚函数表的地址

  int **vtb1 = (int **)*(int **)&persion;
  for (int i = 0; i < 2 && *vtb1 != NULL; ++i)
	{
	  FuncPtr  func = (FuncPtr)*vtb1;
	  func();
	  ++vtb1;
	}

  while (*vtb1)
	{
	  cout << "*vtbl == " << *vtb1 << endl;
	  ++vtb1;
	}
//
//  persion.print ();
//  persion.job ();

  return 0;
}