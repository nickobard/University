#include <iostream>
using namespace std;


void conversion(const Animal &base){
  cout << "some conversion from Hog to Animal" << endl;
  return;
}

class Animal {

};

class Hog : protected Animal {

};

int main (){

  Animal a;
  Hog h;
  // No, because public becase protected. Cannot be used as interface, therefore this operation cannot be done.
  // conversion(h);
  
  return 0;
}