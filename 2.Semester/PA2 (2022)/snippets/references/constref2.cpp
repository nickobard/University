#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string::size_type sizeCnt(string &s){
  string::size_type size = 0;
  for (char c : s){
    size ++;
  }
  return size;
}

string::size_type sizeCntGood(const string &s){
  string::size_type size = 0;
  for (char c : s){
    size ++;
  }
  return size;
}

void strAnalyze( const string &s ){
  cout << s << endl;
  //cout << sizeCnt(s) << endl; // cannot pass const, that means that the
  // problem sustains, so we that only one function limits us completely.
  // Therefore there should be const reference too.
  string copy = s; // this can solve this problem, but is inefficitent.
  cout << sizeCnt(copy) << endl;
  return; // btw this is also an option with void functions.
}

void strAnalyzeGood( const string &s ){
  cout << s << endl;
  cout << sizeCntGood(s) << endl;
  return;
}

void justReturn(){
  //return void; // ERROR
  return strAnalyzeGood("A have returned form void to void!!!"); //OK
  //very useful with recursions
}

int main (){
  string str = "Hello world!";
  cout << sizeCnt(str) << endl; // that works with nonconst strings
  // cout << sizeCnt ("Hello world!") << endl; // ERROR, because we the reference is not const, we cannot then use it with const values.
  // Therefore such implementation only limits us, and should use const to allow such things.
  cout << endl;
  strAnalyze (str);
  strAnalyze("Heeeeeeeey!");
  strAnalyzeGood(str);
  strAnalyzeGood("this is more efficient, use const!!");
  cout << endl;
  cout << sizeCntGood("Yeah, that is much better!") << endl;

  int * ptr = nullptr; 
  const int * cptr = ptr; // YES
  //int * ptr2 = cptr; // NOPE
  // same with references

  justReturn(); // this is an example of how to use return of void 
  // this is very useful with recursions
  return 0;
}