#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
/**
 * Word counter program
 * 
 */
int main (){

map<string, int> word_count;
string word;

  while (cin >> word){
    /**
     * here we initialize the second value with 1
     * 
     * Next time, when we try to insert same value,
     * it won't be inserted, and will return the pair
     * with the iterator on the same element in the map.
     * 
     * The second value will be bool and will be the false value.
     * We will detect that and manually increment the counter value.
     * 
     * So it will work complete in the same way.
     */
    auto ret = word_count.insert({word,1});
    // return type is a pair!! It is not pointer.
    // the first value is the iterator to the value_type, which is a pair!!  
    if (ret.second == false)
    // here that is why we may use the prefix increment, 
    // because it has less priority. The postfix increment may break it
    // it is left to right, so it won't be really a prolem in this case
      ++ret.first->second;
  }
  // a is a pair
  for ( const auto &a : word_count )
    cout << a.first << " " << a.second << endl;
  return 0;
}