#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main (){
	cout << "Specify the file path:" << endl;
	string s1;
	//try to read the file path, if wrong - error
	if ( !getline (cin, s1)){
		cout << "Wrong input." << endl;
		return 1;
	}
	// try to to open file, if is_open return false, then smth went wrong
	fstream os1;
	os1.open(s1);
	if (! os1.is_open())
	{
		cout << "File not found!" << endl;
		return 1;
	}
	// if (!os1.open(s1)){
	// 	cout << "File do not exists." << endl;
	// 	return 1;
	// }
	string s2;
	string s3;
	string s4;
	// getline read the file input, and stores it for each string
	getline(os1,s2);
	getline(os1,s3);
	getline(os1,s4);
//	If after last second line was the EOF, the print it that EOF was found
	if (os1.eof()){
		cout << "EOF was encountered" << endl;
	}
	//print all strings
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	// Close the file and release buffer allocatd
	os1.close(); // becuase streams are objects they have destructors and therefore this closing si unnessecary
	return 0;
}