#include <iostream>
using namespace std;
int & foo(int b){
	int a = 5;
	a += b;
	return a;
}

int main(){
	int &x = foo(5);// no segmentation fault by this time.
	// here we just assigning the reference - address. We are not using
	// value of that address yet(which variable is nonexistent right now)
	// that means that when we initialize the reference, we don't use
	// dereference
	// i.e. this will cause segfault:
	//x = foo(); //here we don't initialize. It is imposible to reinitialize the reference. So here is used dereference of x and foo()
	// which is double segfault in our case
	int &y = foo(10);
	cout << (x + y) << endl; //double segfault
	return 0;
}