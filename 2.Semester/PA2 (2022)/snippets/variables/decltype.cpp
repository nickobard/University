#include <iostream>
using namespace std;

bool f(){
  return true;
}

int main(){
  decltype(5 + 3) i; // i is int
  decltype(5 == 3) j; // j is bool
  // interesting... expression is not evaluated,
  // but we already have a type... Cool!
  
  // When we have function, it deduces from its return time
  // and works fine too
  decltype(f()) b = false;
  // so using literals top-level const is not preserved...
  decltype(42) c;

  return 0;
}