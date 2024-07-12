#include <iostream>
using namespace std;
void foo ( const char * &a){ //tady dostavame referenci
	// a ukazuje na 'e'
	a += 2; // a ukazuej na 'l'
}
void bar ( const char * a){ // dostavame kopii pointeru na ten samy
							// string "Hello world!", ale nemame
							// moznot jej nijak menit, protoze mame
							// const char, ale pointer neni
							// const (neni to const char * const),
							// takze muzeme menit hodnotu a, tedy
							// adresu, na jaky prvek ukazuje
	a ++; // a ukazuje na 'e'
	foo (a); // odsud a ukazuje na 'l'
	a ++; // a ukazuje na 'o'
	cout << a << endl; // o world!
}
int main (){
	const char * x = "Hello world!"; // pointer muzeme menit, ale nesmime pres ten pointer menit hodnotu
	bar (x); // x predavame ne jako kopii. Zadna reference, tedy nic
			// se nezmenilo a x je stale "Hello world!"
	cout << x << endl; // Hello world!
	return 0;
}