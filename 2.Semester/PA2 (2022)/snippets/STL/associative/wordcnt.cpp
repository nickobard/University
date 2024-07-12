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

  map <string, size_t> word_count; 
  string word;

  set<string> exclude;
  exclude.emplace("The");
  exclude.emplace("But");
  exclude.emplace("And");
  exclude.emplace("Or");
  exclude.emplace("An");
  exclude.emplace("A");
  exclude.emplace("the");
  exclude.emplace("but");
  exclude.emplace("and");
  exclude.emplace("or");
  exclude.emplace("an");
  exclude.emplace("a");




  while (cin >> word)
    ++ word_count[word]; // access size_t using word
    // that will reterne reference to the size_t, 
    // which will be the incemented

  /**
   * This is very interesting...
   * So we iterate through pairs int the map...
   * Well, that make sense of course.
   */
  for( const pair<string, size_t> &w : word_count ){
    if ( exclude.find(w.first) == exclude.end())
      cout << w.first << " occurs " << w.second
          // interesting, that we can use in a such way ternary operator!
           << ((w.second > 1) ? " times" : " time" ) << endl;
  }
    //cout << word_count[1] << endl; // we cannot subscript using value
  return 0;
}