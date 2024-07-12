#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
using namespace std;

int main (){
  vector<int> vec;
  fill_n(back_inserter(vec), 42, 69); //adds 42 ints with value 69
  // that is muuch more convinient than write for loop. So it is good to use this thing instead of plain for cycle. Less code, more friendly for the user.
  
  return 0;
}