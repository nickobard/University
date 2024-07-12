#include <map>
#include <set>
#include <iostream>
using namespace std;

 struct strLenghtCmp{
      bool operator () (const string &lhs, const string &rhs) const {
        return lhs.size() <= rhs.size();
        
      }
    };

int main(){

  multiset<string, strLenghtCmp> myset;
  myset.insert("as");
  myset.insert("sd");
  myset.insert("fd");
  myset.insert("gewg");
  myset.insert("wegg");
  myset.insert("aqwe");
  myset.insert("sdff");
  myset.insert("fasfsafsd");
  myset.insert("sdfsdfsdf");
  myset.insert("afasdfsdffsdf");
  myset.insert("asafdsdfsdfsdf");

  for ( const auto &el : myset){
    cout << el << endl;
  }

  cout << "----------------------------------" << endl;

  cout << *myset.lower_bound("\0aaaa") << endl;
  cout << *myset.lower_bound("\0zzzz") << endl;
  cout << *myset.lower_bound("\0aaaa") << endl;

  cout << *myset.upper_bound("\0fasd") << endl;

  //cout << *myset.upper_bound("zzzz") << endl;

  
  return 0;
}
