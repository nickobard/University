#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

string format (string number){
	number = "+" + number;
	return number;
}

bool valid ( string number ){
	if (number.size() != 12 ) // if size of the phone number isn't 12 numbers
		return false;
	if ( number[0] == '0')
		return false; //our phone number cannot start with the 0
	for (char &c : number)	// if character isn't a digit, return false
	{
		if (!isdigit(c))
			return false;
	}
	
	return true;
}

/* PersonInfo is a struct to store name and different phone numbers
 * string represents a name of the person
 * vector represents a container of strings, that represents phone numbers
 * for each person
*/
struct PersonInfo {
	string name;
	vector<string> phones; // we need different phone numbers
						   // therefore we store multiple strings in vector
};

int main () {
	string line; // we need some buffer to iterate each line and 
				 // then store it in the PersonInfo structures
	string word; // This is used to distinguish each word in the line
				 // and store it in the vecotr of strings
	vector<PersonInfo> people; // container foreach person, where we can access each phone number and name. Bacically stores those structs PersonIfno in the container variable people
	cout << "Give data in format <name, phone numbers> without <> symbols:" << endl;
	while (getline(cin, line)){
		//until an error, which may be an EOF
		istringstream record;
		record.str(line); //The line is stored in the memory, and we want to establish the stream with that line in the memory
		PersonInfo info; //Create a struct in the stack
		record >> info.name; // we know that the input has the first string literal as a name, those after that if any are phones
		while (record >> word) //now we should go through the rest of the string and read every word
		{
			info.phones.push_back(word); 
			//record >> info.phones is invalid, because we should use functions to store every object

		}
		people.push_back(info); //store the final struct in the container. Every next while cycle will initialize new struct and reread each line.
	}

	/*
	 * Now we want to write the output, validate our numbers and format them
	 * The phone number is valide when it is 12 numbers : xxx'xxx'xxx'xxx 
	 * without ' character and whitespaces. It should not start with the 0.
	 * And it sould consist only from numbers.
	 * 
	 * The formating is, that it will append from the beginning plus sign '+', so it looks +xxxxxxxxxxxx
	 * 
	*/

	cout << "\n";

	for ( const auto &entry : people) // we use here const aout &, because we want use it as reference, we don't want to change what is inside and for now we don't care what is the type inside the people, we work with that in abstract
	{
		ostringstream formatted, badNums;
		for (const auto &nums : entry.phones)
		{
			if (!valid(nums)){
				badNums << " " << nums; // string in badNums
			} else
				formatted << " " << format (nums) ;
		}
		if ( badNums.str().empty()){
			cout << entry.name << " "
				 << formatted.str() << endl;
		}
		else {
			cerr << "input error: " << entry.name
			     << " invalid number(s) " << badNums.str() << endl;
		}
		
	}
	

	return 0;
}