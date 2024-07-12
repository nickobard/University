#include <algorithm>
#include <iostream>

using namespace std;

int main (){

  int * arr = new int [10];
  
  cout << "sizeof arr: " << sizeof(arr) << endl; // 8 size of pointer...
  // so there is no way ho to find allocated array size

  // auto result = end(arr); // so it should be const - const array..

  const int * arr2 = new int [10];
  // auto result2 = end(arr2); // nor this we can use...
  // for dynamic array there is just no way. We should know the size.

  int arr1 [] = {1,2,3};
  //auto result3 = count(begin(arr1), end(arr1));
  // count returns how often that valie appears!

  delete [] arr;
  delete [] arr2;
  return 0;
}