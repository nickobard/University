#include <iostream>
using namespace std;

void moreSwap (int x, int y){
  swap (x,y); // here is used std::swap, because our own homwbrew swap
  // is not declared it. It is after our moreSwap function, so there 
  // is only one opiton for compiler - to use std::swap
}

void swap (int x, int y){
  int tmp = x;
  x = y;
  y = tmp;
  cout <<"Homebrew swap." << endl;
}

void evenMoreSwap (int x, int y){
  swap (x,y); // Here it uses our homebrew swap, because at this
  // line of code, homebrew swap, is at least declared. Therefore is used.
}


int main (){
  int x = 5, y = 10;
  cout << "x : " << x <<"\ny : " << y << endl;
  swap (x,y); //uisng std::swap - without std cannot use
  // after defining our own swap, std::swap is not used.
  cout << "x : " << x <<"\ny : " << y << endl;
  swap(x,y);
  
  moreSwap(x,y);
  evenMoreSwap(x,y);
  return 0;
}