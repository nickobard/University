#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main (){
  int * ptr = new int (10);
  cout << *ptr << endl;
  delete ptr;

  string * pstr = new string ("Hello world!");
  cout << *pstr << endl;
  delete pstr;

  vector<int> *pvtr = new vector<int>{1,2,3,4,5,6,7,8,9};
  cout << pvtr->at(0) << endl;
  delete pvtr;

  cout << endl;

  int x = 42;
  int * pint = &x;
  int *& rptr = pint;
  if ( rptr == pint ){ // TRUE
    cout << "rptr == pint" << endl; 
    cout << "rptr points to : val : " << *rptr << endl;
  }
  
  return 0;
}