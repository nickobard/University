#include<iostream>
using namespace std;

int main(){
  //char x = 300; // warning - overflow
  char x = 120;
  x <<= 2;
  cout << (int) x <<endl; //-32 - overflow
  return 0;
}