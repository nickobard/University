#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main (){
  typedef map<int, map<string, size_t>> map_out;
  typedef map<string, size_t> map_in;

  // The only way to initialize map with the intial valuse is to use
  // initializer list.
  map_in map1 = {{"Hiya!", 42}};
  // OK, initialize with the empty pair...
  // Same way bit written differently. Uses constructor.
  map_in map4 ({  {"TEST", 1},
                  {"PROGTEST",2},
                  {"TEST", 3}     });

  // That is the another way to initialize the map inside the mape,
  //  just to use same syntax as with initializing inner map
  //  as it was separate map.
  // initializing map with initialized map inside:
  map_out map2 = {
    { 60,   {  {"Hiya!", 42},
               {"Avada", 42},
               {"Kedavra!", 42} }},
    { 314,  {  {"For",1},
               {"The",2},
               {"Emperor!", 3}  }}
    };

    for_each(map2.begin(),map2.end(),
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