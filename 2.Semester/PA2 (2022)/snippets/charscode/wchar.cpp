#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(){
  cout << L"Русский" << endl;
  wcout << L"Русский" << endl;
  cout << "Русский" << endl;
  cout << u8"Русский" << endl;
  string str = u8"Русский";
  cout << str << endl;
  cout << str.size() << endl;
  str = u8"Russian";
  cout << "Russian: size : " << str.size() << endl;
/*
  cin >> str;
  cout << str << endl;
  cout << str.size() << endl;

  size_t size = str.size();
  for ( size_t i = 0; i < size; i++){
    cout << str[i];
  }
  cout << endl;
*/
  wstring wstr = L"šěččěšč";
  wcout << wstr << endl;
  cout << setfill('-') << setw(50) <<"" << endl;
  return 0;
}