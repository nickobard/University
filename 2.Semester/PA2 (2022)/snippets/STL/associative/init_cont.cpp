#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main (){
  vector<string> names = {"John", "Chris", "Martie", "Annie", "Annie", "Saskie"};
  set<string> snames (names.begin(), names.end());
  /**
   * Very interesing, that this is an alphabetic order.
   * That is because set is a BST, thus the set is always
   * sorted
   */
  for (const auto &n : snames )
    cout << n << endl;
  return 0;
}