#include <iostream>
#include <iomanip>
using namespace std;
int main(){
	int x = 10, &y = x;
	int z = 0;
	z = y;
	cout << "val: z : " << z << endl;

	float f = 1.1f, &rf = f;
	z = rf;
	cout << "val: z : " << z << endl;
	cout << setfill('-') << setw (12) << "" << endl;
	
	int i1 = 50;
	int i2 = 123;
	cout << "val: i1 : " << i1 << endl;
	cout << "val: i2 : " << i2 << endl;
	int &ri = i1; cout << "&ri = i1 // = " << i1 << endl;
	cout << "val: ri : " << ri << endl;
	ri = i2; cout << "ri = i2 // = "<< i2 << endl;
	cout << "val: ri : " << ri << endl;
	cout << "val: i1 : " << i1 << endl;
	cout << "val: i2 : " << i2 << endl;
	return 0;
}