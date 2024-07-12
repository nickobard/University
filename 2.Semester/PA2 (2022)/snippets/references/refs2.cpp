#include <iostream>
using namespace std;
//function foo return the reference to a, it doesn't create 
//new variable to store that a
//compiler even will warn us that we are doing something bad.
int & foo(){
	int a = 15;
	//return the reference to a
	return a;
}
int main (){
	int x = 10;
	int &y = x;
	cout << "val: y : "<< y << endl;
	// int &foo(), which is reference to a, which by this point
	// doesn't exist and its address on stack is unreserved 
	// by program. It doesn't belong to us.

	// foo(); - warning, but no segmentation fault
	//	y = foo (); //segfalult, to assign we should dereference foo()
	// reference, which cause segfault
	// so using the reference to nonexisetent local will try to access the
	// memory that is not reserved for us
	// -> Segmentation fault
	
	return 0;
}