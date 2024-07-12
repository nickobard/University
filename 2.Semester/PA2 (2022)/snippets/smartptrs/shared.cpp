#include <iostream>
#include <memory>
#include <string>
using namespace std;

void process (shared_ptr<string> psh){
  cout << *psh << endl;
}

int main (){
  shared_ptr<string> p1;
  //cout << *p1 << endl; segmentation fault.
  // => shared_ptr doesn't create string?
  // How its constructor then looks like?

  p1 = make_shared<string>();
  cout << *p1 << endl; // prints empty string.
  cout << *make_shared<string>() << endl; // again prints empty string
  string str ("Hello World!");

shared_ptr<string> p2;
p2 = make_shared<string>(str);
cout << *p2 << endl;
str = "Hiya!";
cout << *p2 << endl;
cout << str << endl;
string * pstr = &str;

//shared_ptr<string> p3(pstr); 
//cout << *p3 << endl; // invalide, because is allocated on stack
// even without dereferencing we will have an error - becuase shared pointer will try to delete this address - error.
// using make_ptr we will be safed form such a problem creating just a copy. That is much more safier.

string * pstr2 = new string (str);
cout << *pstr2 << endl;

shared_ptr<string> p3(pstr2);

//delete pstr2; // shared pointer p3 will delete deleted object
// while its destruction. That is again why it is dangerous to use
// initialization with new.

string *x(new string("Hey!"));
process(shared_ptr<string>(x));
//cout << *x << endl; // error, because we have passed it into shared ptr,
// it was delted. Now we cannot derefernce it in any way.

  return 0;
}