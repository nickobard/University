#include <iostream>
#include <map>
using namespace std;

bool cmp2 (int lhs, int rhs){
  return lhs < rhs;
}

class Base{
  public:
    static bool cmp (int, int);

    // inside should be a pointer to comparator, defined here.
    // using just like that causes segmentation fault..
    // map<int,int,decltype(cmp)*> my_map; 

    // decltype(cmp) *f = cmp; // ok, points to the cmp, is a pointer
    // just cannot use with statics..
    // and cannot use with cmp2...
    // map<int,int,decltype(cmp2)*> my_map(cmp2); 
  // it doesn't like, that cmp is Base::cmp..
    static constexpr decltype(cmp) * f = cmp;
    map<int,int, decltype(cmp)*> my_map(decltype(cmp));
    // map<int,int, decltype(cmp2)*> my_map(cmp2);


    // void print();
};
// that worked without that function..
/* 
bool Base::cmp (int lhs, int rhs){
  return lhs < rhs;
} */
/* 
void Base::print(){
  for ( const auto &p : my_map){
    cout << p.first << " " << p.second << endl;
  }
} */


 bool Base::cmp (int lhs, int rhs){
   return lhs < rhs;
 }


int main (){
// ok, here it works fine.. Because map is out of the class? Is not a class member??
// works fine...
  map<int,int,decltype(cmp2)*> my_map (cmp2);
  my_map.emplace(2,4);
  my_map.emplace(3,4);
  my_map.emplace(4,4);
  my_map.emplace(5,4);
  my_map.emplace(1,4);

  for ( const auto &p : my_map){
    cout << p.first << " " << p.second << endl;
  }

/* 
  Base b;
  b.my_map(Base::cmp).emplace(4,5); */
 /*  
  b.my_map.emplace(4,5);
  b.my_map.emplace(3,5);
  b.my_map.emplace(1,5);
 */
  // b.print();

  
  return 0;
}