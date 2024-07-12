#include <iostream>

using namespace std;

class TClass {
	int c_p, c_q;
public:
	TClass () {c_p = 0; c_q = 0;} // same as function definiton, don't need a semicolon ';'
	TClass (int fp) {c_p = fp; c_q = 0;}
	void print () { //member functions
		cout << "c_p is: " << c_p << endl;
		cout << "c_q is: " << c_q << endl;
	}
}; //the class definition is same as the struct definition, so here should be semicolon ';'

int main (){
	TClass a, b(123);
	// NOTE, that after declaration of class objects, we cannot call the construktor again
	// SO this is WRONG:
	//	a.TClass(123) - ERROR
	a.print();
	b.print();
	a = TClass (123); // BUT this is valid!
	a.print();
	return 0;
}