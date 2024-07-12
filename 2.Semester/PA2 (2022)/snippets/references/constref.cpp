#include<iostream>
using namespace std;
// is this const int &a automatic local object?
// Does that means that it will be destroyed after the control change?
void foo(const int &a){}
void foo3(int &a){}
const int &bar(const int &a){
  return a;
}
void foo2(const int *a){}

int main (){
  foo(10);
  int x = bar(10); // I am suprised... Ok, that somehow works. Why?
  // the bar returns reference to the passed value of 10. What is that value? That is definitely local variable, which will exists through the functions and after assignment will be destroyed?? So its lifetime ends right after the assignemnt to the x. X just copy its value.
  // const int &y = bar(10); 
  // cout << y << endl; // that will be compiled, but it is accessing unknown undefined address, becuase the 10 after assignment destroys.
  // Just remember that.
  cout << x << endl;

  //foo2(&10);// error, that is not possible.
  //foo3(10); This is also bad.
  // compiler says that the 10 is an int type... This is misleading...

  return 0;
}