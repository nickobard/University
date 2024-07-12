#include <iostream>
using namespace std;

void Bar (){
  throw 42;
}

void Foo () {
  try{
  Bar();

  }
  catch (int x){
    cout << x << endl;
    throw 442;
  }
}


int main () {

  try{
    cout << "Try!" << endl;
    Foo();
  }
  catch(int code){
    cout << code << endl;
  }

  try {
    throw 10;
  }
  catch (int code){
    cout << code << endl;
  }

  return 0;
}