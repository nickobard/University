#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

/* Notes about phone numbers
 * phone number should be stored as string, because
 * - we don't need math for them
 * - we use strings operations with phone numbers
 * - phone numbers are intended to be as-is
 * - phone numbers can have leading zeros
 *  
*/

/* CContacts class represents storing contacts from input
 * and allowing to find each record using name request,
 * where each name from input will find each record, where the name
 * matches with name or surname, then print it out and print the
 * number of matched contacts
 * 
 * The input is one file with contacts at the beginning and requests
 * at the end.
 * Contacts and requests are separated with empty line.
 */
class CContacts {
private:
    //Data type for storing each person
	struct TPerson{
		string m_name  ;
		string m_sname ;
		string m_pnum  ;
	};
public:
    // Constructor
    // Accepts fstream as input and ostream as output. Tie it both.
	CContacts ( ifstream &is, ostream &os ) 
	: c_is (is), c_os (os)  {c_is.tie(&c_os);} 
    // Class interface
	bool read ();
	void print_records () const;
	void matches () const;
private:
		// Class private member functions
	inline void print_person(const TPerson &) const;
	bool read_line(istringstream &);
	bool valid () const;
		// Class private member variables
	ifstream &c_is ;
	ostream &c_os ;
    // Database members
	TPerson c_info;
	vector<TPerson> c_people;
};
  // member fucntion that reads all contacts from file input
  // until empty line is encountered
bool CContacts::read (){
	string line;
	while (getline(c_is, line)){
		
		istringstream record ;
		if (line.empty()){ break; }

		record.str(line);

		if ( !read_line (record) )
		{
			//cout << "Wrong input." << endl;
			return false;
		}
		c_people.push_back(c_info);
	}
	return true;
}
  // Read each line from contacts file, check it for validity and 
  // store name, surname and phone number to TPerson structure
  // Then store it into the vector container.
bool CContacts::read_line( istringstream &is )
{
	string end;
	if ( !(is >> c_info.m_name 
			  >> c_info.m_sname
			  >> c_info.m_pnum  ) ) { 
		return false;
	}
	if( is >> end ){
		return false;
	} 

	if (!valid()){
		return false;
	}
	return true;
}
// Check if the phone number is valid,
// if size of the phone number is exactly 9 numbers,
// if there is no 0 at the start
// and if all characters are digits
bool CContacts::valid () const {

	if (c_info.m_pnum.size() != 9 ) 
		return false;
	if ( c_info.m_pnum[0] == '0')
		return false; 
	for (char c : c_info.m_pnum)	
	{
		if (!isdigit(c))
			return false;
	}
	
	return true;
}

/* 
 * This function will print the contacts list
 * So every person will be printed out
 */
void CContacts::print_records () const {
	c_os << "Stored records:" << endl;		
	for ( auto &a : c_people ){
		print_person (a);
	}
}

// Print one given person
// supplemental private member function
inline void CContacts::print_person(const TPerson &p) const {
		c_os << p.m_name << " " << p.m_sname << " " << p.m_pnum << endl;	
}
// After empty line separator read each request as line
// and check if request name matchs and contact.
// If matches -> counter ++ and print that person
// At the end of the searching cycle, print number of matches
void CContacts::matches() const{
	string request;
	while (getline(c_is, request))
	{
		int cnt = 0;
		for (auto &p : c_people )
		{
			if ( (request == p.m_name ) 
			||   (request == p.m_sname) )
			{
				print_person(p);
				cnt ++;
			}
		}
		c_os << "-> " << cnt << endl;
	}

}
// Given progtest function, provides streams where it will be checked.
bool report ( const string & fileName, ostream & out )
{
  ifstream fis (fileName);
  if (!fis){return false;}
  CContacts contacts ( fis, out );
  if (!contacts.read()) {return false;}
  contacts.matches();

  return true;
}

#ifndef __PROGTEST__
int main ()
{
  ostringstream oss;
  oss . str ( "" );
  assert ( report( "tests/test0_in.txt", oss ) == true );
  assert ( oss . str () ==
    "John Christescu 258452362\n"
    "John Harmson 861647702\n"
    "-> 2\n"
    "-> 0\n"
    "Josh Dakhov 264112084\n"
    "Dakhov Speechley 865216101\n"
    "-> 2\n"
    "John Harmson 861647702\n"
    "-> 1\n" );
  oss . str ( "" );
  assert ( report( "tests/test1_in.txt", oss ) == false );
  return 0;
}
#endif /* __PROGTEST__ */
