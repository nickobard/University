#include <iostream>
using namespace std;

struct TStruct{
	int a; // member variable
	void foo (int a); //member function
};
	// because the foo is the member function of TStruct, so we should call it usign :: scope operator, to use this function from particular struct scope
	// moreover, we can define our member functions out of the scope, where it was only declared. But of course we should use the scope operator to refer to the appropriate scope or struct type (or just type) 
void TStruct::foo(int a){
	cout << "Local: " << a << endl;
	cout << "Global member variable using this operator: "
	     << this -> a << endl;
	//there is another way:
	cout << "Global member variable using scope operator: "
	     << TStruct::a << endl;
}

int main(){
	TStruct struct1;
	struct1.a = 10;
	struct1.foo(6);
	return 0;
}