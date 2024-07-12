//variables/initializer.cpp
#include <iostream>
using namespace std;

int main (){
  double price = 3.14, discount = price * 0.90; // OK
  cout << price << " " << discount << endl;

  // double discount2 = price2 * 0.80, price2 = 3.14; // ERROR
  // price2 wasnt declared yet.

  // string literals are always concatenated by compiler into one literal
  // if there are only whitespaces between them
cout << "Hello "

        "World""!" 
        << endl; // OUTPUT: Hello World!
  
  //int x = 09; // invalid, in octal there is no 9 digit

  extern int y;
  //y = 10; exit - undefined reference to y 
  extern int y; // OK 
  //int y; //compile error
  //extern int y = 10; //error, has both extern and initializer
  // how can we then define extern? It should be defined in the other translation unit, in the other cpp file. This on should be used in the hpp file, and somewhere in the cpp should be defined int y
  return 0;
}