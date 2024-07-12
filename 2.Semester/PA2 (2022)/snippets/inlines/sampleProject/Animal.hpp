#pragma once
#include <iostream>
#include <string>
using namespace std;

class Animal{
  public:
    static void initAnimal() ;
    static void SayHi() ;
  private:
    static string type_;
};

#ifndef __ANIMAL__
string Animal::type_;
#endif

inline
void Animal::SayHi() {
  cout << type_ << ": Hi!" << endl;
}

inline
void Animal::initAnimal() {
  type_ = "Animal";
}