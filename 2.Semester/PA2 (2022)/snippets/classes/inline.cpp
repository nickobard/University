#include <iostream>
using namespace std;

inline
void foo(){
  cout << "Inline!" << endl;
}

int main (){
  // in gdb are not inlined... Because of -ggdb option?
  foo();
  foo();
  return 0;
}
