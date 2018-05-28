//
// Created by 陈国威 on 2018/3/25.
//

#include <iostream>

using namespace std;

class Person
{
 public:
  Person(): mId(0), mAge(20)
  {

  }
  void print()
  {
    cout << "id: " << mId
         << ", age: " << mAge << endl;
  }


 private:
  int mId;
  int mAge;

};

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

