// Problem is that we cannot define same global in several TUs
// Therefore it should be defined only once, and here we use define to solva such a problem
// Important is that the rest of the object definition is here.
#define __ANIMAL__
#include "Animal.hpp"

int main () {
  Animal::initAnimal();
  Animal::SayHi();
  return 0;
}