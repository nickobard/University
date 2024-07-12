#include<iostream>
using namespace std;
int foo (int a){
	return 10;
}
const char * foo (double b){
	return "Hello world!";
}
int main (){
	int x;
	x = 'a';
	cout << "val: x : " << x << endl; // 97
	cout << foo('a') << endl; // 10
	// pri pretezovani dojde k promoce char - > int a bude vitez - *P
	// pri double by doslo ke konversi - S
	return 0;
}