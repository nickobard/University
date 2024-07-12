#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main (){
  vector <int> vec = { 5,4,3,5,6,1,1,2,1,1,2,3,4,1,1,1};
  int cnt = 0;
  auto f = [cnt](vector<int> &src) mutable -> void {
    src.push_back(42); // not const, now we can add elements.
    cnt++;
    cout << "Counter: " << cnt << endl;
  };

  f(vec); // 1
  f(vec); // 2
  f(vec); // 3 - so f now is an object
  cout << "Actual counter: " << cnt << endl;
  // the cnt is copied. It is now local variable fo the f object.
  
  auto p = [](const vector<int> &src){
    for_each(src.cbegin(),src.cend(),[](int el){ cout << el << " ";});
    cout << endl;
  };

  p(vec);
  int num = 42;
  transform(vec.begin(),vec.end(),vec.begin(),
            [num](int el) ->int { if (el < num) return -el; return el;});
  p(vec);
  // very good. Now i can use those functions.
  return 0;
}