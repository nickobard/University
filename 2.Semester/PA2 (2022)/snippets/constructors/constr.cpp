#include <iostream>
using namespace std;

/* It looks like for initializing built-in data types 
 * it doesn't matter what type of constructor we use.
 * 
 * But user declared constructor prevents a class from being aggregate.
 * So there is such a difference between them.
 * 
 * Basically we use default constructor to create object without explicit
 * initialization, without neccessary parameters.
 * Therefore the initialization of built in data types is similar
 * using both
 * 
 * The example with the Goat class uses same process of initialization as 
 * user declared default constructor and also prevents class to being 
 * aggregate
 * 
 * So there is no difference in type of constructor between Cat and Goat
 * both use user declared constructor (which, again, prevents their classes
 * being aggregate)
 * 
 * Using default we explicitely say, that consider this user declared
 * default constructor as defaulted default constructor, generated
 * by the compiler. 
 * 
 * Again, initialization is completely similar. (But maybe DDC is more 
 * faster, because they are implicitely inline, so it can be
 *  basically faster)
 */
class Dog {
	// using defaulted default constructor.
	int x, y ,z;
	public:
	const Dog & printAll() const{
		cout << "Dog: // zadny konstruktor -> compiler generated constructor aka defaulted default constructor" << endl;
		cout << "val: x : " << x << endl;
		cout << "val: y : " << y << endl;
		cout << "val: z : " << z << endl;
		cout << endl;
		return *this;
	}
};
class Cat {
	int x, y, z;
	public:
	Cat (){}
	const Cat & printAll() const{
		cout << "Cat: // user declared default constructor (no parameters and no body statements)" << endl;
		cout << "val: x : " << x << endl;
		cout << "val: y : " << y << endl;
		cout << "val: z : " << z << endl;
		cout << endl;
		return *this;
	}
};
class Horse {
	int x, y, z;
	public:
	Horse () =default;
	const Horse & printAll() const{
		cout << "Horse: // user declared default constructor with =default keyword -> explicitly said to generate DD constructor" << endl;
		cout << "val: x : " << x << endl;
		cout << "val: y : " << y << endl;
		cout << "val: z : " << z << endl;
		cout << endl;
		return *this;
}
};
class Goat {
	int x, y, z;
	public:
	Goat (int val) : x(val) {}
	const Goat & printAll() const{
		cout << "Goat: // user defined NOT-default constructor, x value always is 5" << endl;
		cout << "val: x : " << x << endl;
		cout << "val: y : " << y << endl;
		cout << "val: z : " << z << endl;
		cout << endl;
		return *this;
}
};
int main(){
	Dog d;
	d.printAll(); // undefined values, all three.
	/*
		Dog: //zadny konstruktor -> compiler generated constructor
		val: x : 21878
		val: y : 1987098544
		val: z : 32767	
	*/
	Cat c;
	c.printAll();
	/*
		Dog:
		val: x : 0
		val: y : 0	// porad jsou nuly - ale stejne je to asi nahodna hodnota
		val: z : 2000421120
		Cat: //user declared default constructor (no parameters)
		val: x : 22035
		val: y : 2109181200
		val: z : 32765
	*/
	Horse h;
	h.printAll();
	/*
		Dog: // zadny konstruktor -> compiler generated constructor aka defaulted default constructor
		val: x : 32694
		val: y : 1049236960
		val: z : 21931

		Cat: // user declared default constructor (no parameters and no body statements)
		val: x : 21931
		val: y : -698829536
		val: z : 32767

		Horse: // user declared default constructor with =default keyword -> explicitly said to generate DD constructor
		val: x : 0
		val: y : 0
		val: z : 1049235712
	*/
	Goat g(5);
	g.printAll(); 
	/*
		Dog: // zadny konstruktor -> compiler generated constructor aka defaulted default constructor
		val: x : -295057555
		val: y : 21945
		val: z : -1860292664

		Cat: // user declared default constructor (no parameters and no body statements)
		val: x : 32531
		val: y : -295057632
		val: z : 21945

		Horse: // user declared default constructor with =default keyword -> explicitly said to generate DD constructor
		val: x : 0
		val: y : 0
		val: z : -295059200

		Goat: // user defined NOT-default constructor, x value always is 5
		val: x : 5
		val: y : -1885377472
		val: z : 32764
	*/
	return 0;
}