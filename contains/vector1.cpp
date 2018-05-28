//
// Created by 陈国威 on 2018/4/30.
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
  // create empty vector for strings
  vector<string> sentence;

  // reserve memory for five elements to avoid reallocation
  sentence.reserve (5);

  // append some elements
  sentence.push_back ("Hello, ");
  sentence.insert (sentence.end (), {"how", "are", "you", "?"});

  // print elements separated with spaces
  copy (sentence.cbegin (), sentence.cend (),
      ostream_iterator<string>(cout, " "));
  cout << endl;

  // Print "technical data"
  cout << " max_size(): " << sentence.max_size () << endl;
  cout << " size(): " << sentence.size () << endl;
  cout << " capacity(): " << sentence.capacity() << endl;

  // swap second and fourth element
  swap (sentence[1], sentence[3]);

  // insert element "always " before elemnt "?"
  sentence.insert (find (sentence.begin (), sentence.end (), "?"), "always");

  // assign "!" to the last element
  sentence.back () = "!";

  // print elements separated with spaces
  copy (sentence.cbegin (), sentence.cend (),
      ostream_iterator<string>(cout, " "));

  cout << endl;

  // print some "technical data" again
  cout << " size(): " << sentence.size () << endl;
  cout << " capacity(): " << sentence.capacity() << endl;


  // delete last two element
  sentence.pop_back ();
  sentence.pop_back ();

  // shrink capacity (since c++11)
  sentence.shrink_to_fit ();

  // print some "technical data" again
  cout << " size(): " << sentence.size () << endl;
  cout << " capacity(): " << sentence.capacity () << endl;

  return 0;
}

