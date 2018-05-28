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
  ~Person ()
  {
    --sCount;
  }

  void print()
  {
	cout << "id: " << mId
		 << ", age: " << mAge << endl;
  }


 private:
  static int sCount;
  int mId;
  int mAge;

};

int Person::sCount = 0;

int main()
{
  Person p1;
  cout << "sizeof(p1)==" << sizeof (p1) << endl;
  int *p = (int*)&p1;
  cout << "p.id == " << *p << ", address: " << p << endl;
  ++p;
  cout << "p.age == " << *p << ", address: " << p << endl;
  cout << endl;

  Person p2;
  cout << "sizeof(p2) == " << sizeof (p2) << endl;
  p = (int*)&p2;
  cout << "p.id == " << *p << ", address: " << p << endl;
  ++p;
  cout << "p.age == " << *p << ", address: " << p << endl;

  return 0;
}