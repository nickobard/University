#include <iostream>
using namespace std;
int main (){
	int i, *a = new int[70];
	for ( i = 0; i < 70; ++i){ // here we use same i - it is not shadowed 
							   // by i in the for cycle, because it is 
							   // same variable.
		//cout << i << " ";
		a[i] = i;
		//cout << a[i] << " "; same output as i
	}
	delete [] a; // note, NOT delete a[]!!!
	cout << '\n' << "val: i : " << i << endl; // 70

	// consider this:
	a = new int [70];
	i = -100;
	for ( int i = 0; i < 70; ++i ){ //here we have local i
		// cout << i << " ";
		a[i] = i;
		// cout << a[i] << " "; //same output as i
	}
	delete [] a;
	cout << '\n' << "val: i : " << i << endl; // -100 - we use outside i
	return 0;
}