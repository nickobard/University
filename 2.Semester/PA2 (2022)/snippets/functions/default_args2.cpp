#include <iostream>
using namespace std;

class Base{

public:
  Base() : m_X(10), m_Y(20) {}
  // cannot do that. Cannot use member variables as default initializers
  void foo(int x /* = m_X */, int y /* = m_Y */) const { 
    cout << x * y << endl;
  }
  int m_X, m_Y;
};

class Hi{
  public:
  // but we can use static!!!
    void foo ( int x = m_X, int y = m_Y){
      cout << x * y << endl;
    }
    // static are global and defualt initialized with 0
    // But why here we cannot use in-class initialization??
    // Should be const, otherwise cannot initialize with variable a want..
  // static  int m_X = 10, m_Y = 20;

  /**
   * Now that make sense:
   * If that wasn't const, each time we create new object, 
   * static would be reinitialized... But that is completely 
   * not bad. And that would not make any sense...
   * 
   * That is why - if we use in-class initialization on the static,
   * we should make it const, otherwise it is imposible to reinitialize
   * static variabe each time we construct our object....
   */
  static const int m_X = 10, m_Y = 20;
  // here we can use such initialization using in-class intializer...

  // That is OK, because m_Z won't be reinitialized.
  // It will be in the program memory, so it just uses it.
  // And while programming we can change this.
  static int m_Z;
  
  int z = 10;
};

// global variable
int g_X = 42;

class Dummy{
  public:
  // that is OK, can use it with global or static variable to defualt intialize.
    void foo(int x = g_X) const {
      cout << g_X << endl;
    }
};

class Progtest{
  public:
  // cannot compile with that... Weird...
  // undefined reference tp c_X;
  // static int c_X ;

  // But with const it works..
  // I think this is because static behaves differently 
  // and is stored differently that globals..
  // Perhaps it can be used only when is initialized with value??
  // That is limiting us very very much... But ok.
    static const int c_X = 24;
    void progtest (int x = c_X){
      // c_X ++;
      cout << x << endl;
    }
    // here it is ok.
    // So while it is static, and not const, we cannot use it as default 
    // initializer variable - so it is only for static constants or globals
    static int m_Y;
    // alse undefined reference... A don't understand. 
    // How then we can use statics in classes?? That is really messy..

    // Ther reason why is simple. No object ownes static members. Only class itself holds it. Object have rights only to use their class member.
    // It is like class is a parent, and his car is a static property of the parent.
    // Tough parent has many children, they don't own the car. 
    // But while they are in the same family, they all can use that car
    // sharing it between each other.
    // Only static functions can use static variables as arguments.
    // Satic functions analogy is to start engine of the car, drive the car.
    // The all works only with car, may use childs arguments as parameters,
    // but those functions still, as a car, doesn't belong to the child itself, which currently wants to drive the car.

    // But of course we can use statics with inside functions, can't we?
    // Yeah, we can
    void test () {
      static int x = 5;
      cout << ++ x << endl;
    }
    // with globals it works also just fine. Globals are seen every where
    // and are accessible for the class.
    void test_progtest(int test = g_X){
      cout << ++g_X << endl;
    }
};

class Honey{
  public:
    static int bee;
    // cannot use it. Static doesn't belong to Honey,
    // therefore honey object doesn't have member bee.
    // Thus, it is undefined reference.

    /* void foo (){ 
      cout << bee << endl;
    } */
    static int getBee(){
      return bee;
    }
    void foo (int x){
      cout << x << endl;
    }
};

int main(){
  Progtest test;
  test.progtest();
  test.progtest(69);

  test.test();
  test.test();
  test.test();
  test.test();

  test.test_progtest();
  test.test_progtest();
  test.test_progtest();

  // Honey h; cannot create object - uses 
  // h.foo();

  Honey h2;
  //  also cannot use. h2.bee is undefined - doesn't exists...
  // h2.foo(h2.bee);
  // again, cannot use...
  // h2.foo(h2.getBee());

  return 0;
}