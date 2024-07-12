#include <iostream>
using namespace std;
class CBase{
	public:
	//So this is the default constructor, it works similarly as the synth constructor, initializing built-in types with undefined values.
	// But without this default constructor I cannot create objects without parameters
	CBase ()
	: m_num1 (50) {}
	CBase ( int a )
	: m_num1 (a) {}
//	CBase () = default; // using this default constructor other won't be initialized. T
	CBase (int a, int b)
	: m_num1(a),
	  m_num2(b) {}

	void print () const {
		cout << "num1: " << m_num1 << endl;
		cout << "num2: " << m_num2 << endl;
	}
	private:

	int m_num1 ;
	int m_num2 ;
};
int main (){
	CBase base1;
	base1.print();
	return EXIT_SUCCESS;
}