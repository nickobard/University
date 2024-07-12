#include <iostream>
using namespace std;
int foo(){
	return 10;
}
int bar ( int & a){
	int x = 10;
	return x;
}
int main (){
	//int &x = foo(); //ERROR
	//int &y = 10; //ERROR
	int z = foo();
	//z = bar(10); //ERROR
	int &x = z;
	cout << x << endl;
	return 0;
}