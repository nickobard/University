
#include <iostream>
using namespace std;

int main () {

  constexpr int x = 10;
  x--; // error, constexpr is implicitly const.

  cout << x << endl;


  return 0;
}