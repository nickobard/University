#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int main () {
  typedef map<int, map<string, size_t>> map_out;
  typedef map<string, size_t> map_in;

  map_out map1;
  // inserts default constructed elements...
  map1.insert({});
  // inserts default constructed map with first element 42, 
  // and the second element with constructed inner map with
  // three elements
  // So there just should be one more bracket inside. 
  map1.insert({42,{ make_pair("Hiya!",69),
                    {"Foo"  ,69},
                    { "Bar" ,60} }});
  
  // map1.insert({},{}); // not valid cannot insert more then one 
  // elements at the time.
  // with no arguments - just implaces defualt constructed elements
  // didn't emplaced, because 42 already exists as a key...
  map1.emplace ( 42, map_in({ {"Badabum", 49} }) );
  // This is the only way I know now how to make emplace with maps.
  // Or use make pair???
  map1.emplace ( 43, map_in({ {"Badabum", 49} }) );
  // A lot of errors. It doesn't match the type - map.
  // map1.emplace ( 43, make_pair("Hero!",24) );
  // Make pair make sense only when we use insert or emplace,
  // TO construct a map, the make pair cannot be applied


    for_each(map1.begin(),map1.end(),
  []
  (const map_out::value_type &out_el)
  { for_each(out_el.second.begin(),
              out_el.second.end(),
    [out_el]
    (const map_in::value_type &in_el)
    {
      cout << out_el.first << " "
            << in_el.first  << " "
            << in_el.second << endl;
    });});

  return 0;
}