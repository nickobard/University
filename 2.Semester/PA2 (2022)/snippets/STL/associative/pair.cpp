#include <iostream>
#include <utility>
#include <string>
using namespace std;

pair <string, int> process(){
  return pair <string, int> ("Hiya", 69);
}

int main(){
  pair <string, int> my_cool_pair = process();
  // first and second are not getters and setters, they are direct
  // public members
  cout << my_cool_pair.first << " " << my_cool_pair.second << endl;

  //another way to use pairs is to use makepairs, which returns a pair
  pair<string, int> my_super_pair = make_pair<string, int>("Avada Kedavra", 42);

  cout << my_super_pair.first << " " << my_super_pair.second << endl;

  return 0;
}