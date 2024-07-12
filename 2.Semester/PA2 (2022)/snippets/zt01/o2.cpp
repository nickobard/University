#include <iostream>
using namespace std;
int bar (int a){
	cout << "val : a : " << a << endl; // 97
	return a * 2;
}
int foo (const int & a){ // take reference to passed const int value
						// How this passed value looks in memory? As unnamed address in the memory, where reference can still be bound?
	cout << "val : a : " << a << endl; // 95
	return bar (a + 2);
}
int main(){
	int x = foo(95); // pass const int value 
	cout << "val : x : " << x << endl; // 194
	return 0;
}