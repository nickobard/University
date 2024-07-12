#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int main (){

  typedef map<int, map<string, size_t>> map_out;
  typedef map< const string, size_t> map_in;


  pair<string, size_t>("Hiya!",42);

  string str = "Hiya!";
  size_t sz = 42;
  int id = 69;

  map<int, map<string, size_t>> my_map;
  map_in my_map2;
  // my_map2.emplace(str,sz);

  // my_map.emplace(id, my_map2); // that is valid. So that will construct the map? Looks like yes..
  // if i will try to make again such emplacte, that will do nothing,
  // because map with such key already exists.
  // Therefore, that is will do nothing.

  // Don't know why this doesn't work...
  // What is the prolem here with it?
  // my_map.insert({42,{}}); // works fine. The map inside is empty object.

  // my_map.insert({id,{}});
  // that works, if i construct map right inside..  Using constructor explicitely.
  string str2 ("Jelly");
  // my_map.emplace(id,map_in());

  for_each(my_map.begin(),my_map.end(),[&](const map_out::value_type &el)
  { for_each(el.second.begin(),el.second.end(),[&](const map_in::value_type &in_el)
  {
    cout << el.first << " " << in_el.first << " " << in_el.second << endl;
  });
  });
  return 0;
}