#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class CInt{
  public:
    CInt (int x) : m_Val(x) {}
    bool operator< (const CInt &rhs) const{
      return m_Val < rhs.m_Val;
    }
    bool operator == (const CInt &rhs) const{
      return m_Val == rhs.m_Val;
    }
    friend ostream &operator<< (ostream &os, const CInt &val){
      os << val.m_Val;
      return os;
    }
    friend int operator+ (const CInt &lhs, const CInt &rhs){
      return {lhs.m_Val + rhs.m_Val};
    }
    friend int operator+ ( const int lhs, const CInt &rhs){
      return lhs + rhs.m_Val;
    }
  private:
    int m_Val;
};

int main(){

      // because we have default operator ==, the find algorithm
      // will work, because the derefernce type supporst operator==,
      // essential for functioning of this algorithm
  CInt arr[] = {1,5,3,6,8,2,4,5,1,7,3,4,6,42};
  auto res = find(begin(arr),end(arr),42);
  cout << (res == end(arr)
          ? "42 is not found."
          : "42 is found.") << endl;

  cout << "{ ";
  for ( const auto &a : arr)
    cout << a  << " " ;
  cout << "}" << endl;

  sort(begin(arr), end(arr));

  cout << "Sorted:" << endl;

  cout << "{ ";
  for ( const auto &a : arr)
    cout << a  << " " ;
  cout << "}" << endl;  

  CInt sum (accumulate(begin(arr),end(arr),(CInt)0));
  cout << sum << endl;

  int sum2 = accumulate(begin(arr),end(arr), 0 );
  cout << sum2 << endl;

  CInt sum3 (accumulate(begin(arr),end(arr),(int)0));
  cout << sum3 << endl;


//==========================STRINGS=====================================

vector<string> vec1 = {"Hiya!","Hello","World!","V is Vendetta"};

/**
 * Interesting that we cannot put "" string - C-style string,
 * but adding s suffix at the end we put there C++-style string!
 * 
 * That is one case where konwing that is very useful!
 */
string ssum = accumulate(vec1.cbegin(),vec1.cend(),""s);
cout << ssum << endl;

char str1[] = "The\0 quick brown fox jumps over the lazy dog.";
char str2[] = "The";
// we should use 4, because there is actually 4 chars that are compared!
// the first squence is 4 chars - "The\0", the second is "The\0"
// It doesn't see that it is a string and neglects the '\0' char
if (equal(str1, str1 + 4, cbegin(str2) ,cend(str2)) ) // Now equals!
  cout << "Equals!" << endl;
else
  cout <<"Not equals!" << endl;


if (equal( str2 ,str2 + 2, str1 ,str2 + 3) ) 
  cout << "Equals!" << endl;
else
  cout <<"Not equals!" << endl;

if (equal(cbegin(str2),cend(str2),cbegin(str1))) // Now works as expected
  cout << "Equals!" << endl;
else
  cout <<"Not equals!" << endl;

return 0;
}