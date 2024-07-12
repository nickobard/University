#include <iostream>

namespace first {
	using namespace std;
	void calc (int a, int b)
	{
		cout << "a * b = " << a * b << endl << "Done!" << endl;
	}
}

namespace second
{
	using namespace std;
	void calc (int a, int b)
	{
		cout << "a + b = " << a + b << endl << "Done!" << endl;
	}
} // namespace second


int main(){
	using std::cout;
	using std::cin;
	using std::endl;

	int a = 0;
	int b = 0;
	
	cout << "Write two numbers:" << endl;
	if (!( cin >> a >> b ) )
		{
			cout << "Wrong input."<< endl;
			return -1;
		}
	first::calc(a,b);
	second::calc(a,b);

	return 0;
}