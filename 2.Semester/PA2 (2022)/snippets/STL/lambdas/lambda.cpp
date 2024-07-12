#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int main (){
  int cnt = 0;
  vector <int> vec = { 5,4,3,5,6,1,1,2,1,1,2,3,4,1,1,1};
  // here we try to modify cnt, but when we capture it,
  // we cannot affect its value - only if reference or explicitely mutable
  // keyword
  for_each(vec.cbegin(),vec.cend(),
        [cnt](int x) mutable {cnt++; cout << x << " ";}); 
        cout << "Total: " << cnt << " elements."<< endl;
  cout << cnt << endl; // still zero... Is it because our labmda is every time recreated again and again? I think so... That would make sense.
  // so we need to create our own labmda as variable, and then it should works, perhaps..
  int num = 1;
    
  partition(vec.begin(),vec.end(),
            [num](int el){ return el == num; });

  /**
   * This lambda is OK, because it doesn't change our vector,
   * But it of course copies the whole vec.. Doesn't it?
   */
  auto f = [vec] 
    { 
      for_each(vec.cbegin(),vec.cend(),
        [](int x){cout << x << " ";});
        cout << endl; 
    };

  f();
  
  return 0;
}