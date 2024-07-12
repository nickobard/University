#include <iostream>
using namespace std;
int main (){
	int x1 = 10;
	int x2 = 20;
	// referenci vzdycky musime inicializovat, jinak to bude chyba
	// int &y;  //ERROR - muusi byt inicalizovan

	// krome toho, reference nemuze byt ukazana na nullptr
	// int &y = nullptr;  //ERROR - nullptr neni typ int&
	// int *py = nullptr;	//OK

	// Da se vsimnout, ze vlastnos, ze int &y musi byt inicializovan
	// napodobuje vlastnost constant:
	// int *const yp;  //ERROR - musi byt inicializovan
	// int * const py = nullptr;	O//K

	// int &y = 0; Toto je taky chyba, nelze int& priradit int,
	// i kdyz to zni docela divne, kdyz umime priradit promennout int.
	// Tedy zjevne problem je v tom, ze ta 0 je nejak konstantni. Tedy nema
	// adresu. Protoze neni to promenna. int& potrebuje adresu existujici promenne.
	// Toto je hlavni rozdil od pointeru, kde tomu tak neni

	int &y = x1; 
	cout << "val: y : "<< y << endl; // -> 10
	// Tady je velmi dulezite, ze referenci umime opravdu zmenit na jinou promennou
	// Zase ale musi ta promenna existovat a mit stejny typ
	y = x2; // OK
	cout << "val: y : "<< y << endl; // -> 20

	return 0;
}