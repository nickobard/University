#include <iostream>
using namespace std;

class MyClass{
  public:
    static void myMethod (){
      cout << "This is my Method! Go find your's!" << endl;
    }
};

int main () {
  MyClass::myMethod();
  return 0;
}