#include <iostream>
#include <map>
#include <string>
using namespace std;

int main (){
  map<string, string> my_map = {  {"John", "Christesctu"},
                                  {"John", "Johnson    "}, // apparently was ignored
                                  {"Anny", "Saskie"     } };
  cout << my_map ["John"] << endl;
  my_map["John"] = "Johnson"s;
  cout << my_map ["John"] << endl;
  cout << my_map ["Johnson"] << endl; // nothing is found, so it prints nothing... interesting
  // So it just added Johnson, but the second value was default initialied.. Very interesting...
  my_map ["Annie"] = "Saskie"; // here we added that.
  cout << my_map["Annie"] << endl;

    cout << "\n" "map records:" << endl;
  for (const auto &a : my_map )
    cout << a.first << " " << a.second << endl;


  map<string,int> my_second_map;
  my_second_map["Hiya!"];
  cout << my_second_map["Hiya!"] << endl; //integer was default initialized as 0

  return 0;
}