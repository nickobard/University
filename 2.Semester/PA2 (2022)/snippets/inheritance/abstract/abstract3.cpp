#include <iostream>

class SuperAnimal {

  public:
    virtual void foo () = 0;
};

void SuperAnimal::foo(){
  return;
}

class SubAnimal : SuperAnimal {
  public:
    virtual void bar() = 0;
};

void SubAnimal::bar(){
  return;
}

class Hog : public SubAnimal {
  public:
  void bar() override {
    return;
  }
  void foo() override {
    return;
  }
};


int main () {
  // Hog should override both foo and bar pure virtuals
  Hog h1;
  return 0;
}