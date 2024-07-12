#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;

int main (){
  pair<int, int> my_cool_pair; //interesting, that in the pair we
  // have default initialized wiht 0 our int value.
  // Or coincidence??
  // And very intersing, that we have included pair here.. Maybe it is included from string too??
  // aha.
  cout << "Apparently for pair we need no library.." << endl;
  cout << my_cool_pair.second << endl;

  set<int> iset;
  for ( int i = 1; i <= 1000000; i++ )
    iset.insert(i);

  if (iset.find(500) == iset.end())
    cout << "500 not found." << endl;

  auto it = iset.begin();
  // this value is ALWAYS one.
  // Does it mean that it is readed in IN order?
  // That would make sense, because in-order algorithm always gives sorted array.. So that is why map and set are so so incredibly cool.. Just wow.
  // Really cool.
  cout << *it << endl;
  

  return 0;
}