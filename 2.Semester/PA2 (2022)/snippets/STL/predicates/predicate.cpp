#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

 auto isShorter(const string &lhs, const string &rhs) -> bool {
  return lhs.size() < rhs.size();
}

auto isTwo(const int el) -> bool { //trailing return
  return el == 2;
}

auto isFive(int  el) -> bool {
  return el == 5;
}

int main(){
  istringstream is ("The quick brown fox jumps over the lazy dog");
  string word;
  vector<string> vec;
  while (is >> word)
    vec.push_back(word);
  
  for ( const auto &w : vec ){
    cout << w << " ";
  }
  cout << endl;

  sort(vec.begin(),vec.end(), isShorter); // using this binary predicate as the third argument
  // interesting, how iterators passes elements to the fucntion..
  // the parameters are not pointers. They are reference. 
  // so I suppose that it dereference iterators to neede elements
  // as arguments

  
  for ( const auto &w : vec ){
    cout << w << " ";
  }
  cout << endl;

  vector<int>  ints = {1, 2, 4, 5, 6,3 ,2 ,3,5,6,7,3,5,2,4,5,8,9,5,7,3,5,62,4,6,7,4,5,7,2,4,6,7,4,8,9,0,1,43,6,3,6,7,4};

  partition(ints.begin(),ints.end(),isTwo); // all two will be on the left

  for ( const auto i : ints){
    cout << i << " ";
  }
  cout << endl;

  ints.erase(find_if(ints.begin(),ints.end(),isFive)); // that won't work properly
  // because find will return the fisrt found element,
  // which will be then by erase as iterator to the element.

  for ( const auto i : ints){
    cout << i << " ";
  }
  cout << endl;

  return 0;
}