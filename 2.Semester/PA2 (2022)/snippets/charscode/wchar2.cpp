#include <iostream>
#include <locale>
#include <string>
#include <cctype>
#include <codecvt>
using namespace std;

int main (){


  //https://stackoverflow.com/questions/50053386/wcout-does-not-output-as-desired?msclkid=3c210c43b80111ec9bcb9e1b0f7c00c7
  ios_base::sync_with_stdio(false);

  locale utf8( locale(), new codecvt_utf8_utf16<wchar_t> );
  wcout.imbue(utf8);
wstring str;
wcin >> str;
wcout << str << endl; //works fine.
for ( auto &c : str){ // doesn't work
  c = towlower(c);
}
wcout << str << endl;

  wcout << L"ščěščěš" << endl;
  return 0;
}