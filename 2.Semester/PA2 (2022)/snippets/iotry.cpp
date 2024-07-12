#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(){
  cout << "Hello!"<< endl;
  cout << "Hello world!" << endl ;
  int value = 0 ;
  cout << "Zadej cislo:" << endl;
  while ( cin >> value )
  {
    cout << "Your value is: "<< value << endl;
  }
  return 1;
}