#include <iostream>
#include <iomanip>

using namespace std;

int main () {

  float x = 0.0f;
  cout << " x : " << x << endl;
  cout << "-x : " << -x << endl;

  cout << boolalpha << " 0 == -0 : " << (x == -x) << endl;
  cout << boolalpha << " 0 <= -0 : " << (x <= -x) << endl;
  cout << boolalpha << " 0 >= -0 : " << (x >= -x) << endl;
  cout << boolalpha << " 0 < -0 : " << (x < -x) << endl;
  cout << boolalpha << " 0 > -0 : " << (x > -x) << endl;


  return 0;
}