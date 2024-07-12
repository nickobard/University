#include <set>
#include <iostream>
#include <iomanip>
using namespace std;

int main (){

  multiset<int> nums;

  for (int i = 0; i < 1000; i++)
    if ( i % 2 == 1)
      nums.insert(i);

  auto ret = nums.upper_bound(401);
  cout << "upper: " << *ret << endl;
  
  ret = nums.lower_bound(401);
  cout << "lower: " << *ret << endl;

  // always returns iterator to the 401 value..  
  return 0;
}