#include <iostream>
#include <map>
#include <iomanip>
#include <string>

using namespace std;

int main (){
  
  multimap<string, string> names;

  names.insert({"John","E"});
  names.insert({"John","A"});
  names.insert({"John","F"});
  names.insert({"John","C"});
  names.insert({"John","D"});
  names.insert({"John","B"});

  for (auto beg = names.lower_bound("John"),
            end = names.upper_bound("John");
       beg != end; ++beg )
       cout << beg->first << " " << beg->second << endl; //they are printed unordered! Printed just as they were added! So it doesn't order them!
       // Interesting, very interesing... I would suppose, that it will order them, but it doesn't do that.
       
    /* OUTPUT
    John E
    John A
    John F
    John C
    John D
    John B
    */

   map<string,string> names2 = {{"Albert","Einstein"},
                                {"Danielson","Christescu"},
                                {"Nickson","Nickolson"},
                                {"Xea","Zzap"}};
  // now our map is ordered.
  cout << setfill('-') << setw(50) << "" << endl;

  for (const auto &a : names2 )
    cout << a.first  << " " << a.second << endl;

  cout << setfill('-') << setw(50) << "" << endl;

  auto ret = names2.lower_bound("Boris");
  cout << "lower: " << ret->first << " " << ret->second << endl;
  names2.insert(ret,{"Boris", "You Miss"});

  for (const auto &a : names2 )
    cout << a.first  << " " << a.second << endl;

  cout << setfill('-') << setw(50) << "" << endl;

  ret = names2.upper_bound("Hello");
  cout << "upper: " << ret->first << " " << ret->second << endl;
  names2.insert(ret,{"Hello", "There"});     


  for (const auto &a : names2 )
    cout << a.first  << " " << a.second << endl;

  // very interesting, that it returned upper value.
  // What does it mean the upper value in the BST?
  // I suppose it depends on the acutal structure. 
  // In example, when we had Boris key, it found the Danielson, but that doesn't have any child, so therefore it cannot return lower. 
  // Hmm, Is lower the parent, and upper the child? Or it depends how we go?
  //because when we go from the left subtree to the root, using LNR,
  // we have it in ascending order, while going to the right subtree,
  // we have it in the descending order.
  // So it is much more complicated/

  cout << setfill('-') << setw(50) << "" << endl;

  ret = names2.lower_bound("Zorro");
  if (ret == names2.end())
    cout << "The end!" << endl;
  
  names2.insert(ret, {"Zorro", "You Dead"}); //when the ret is end, it still can insert! Great! 

  for (const auto &a : names2 )
    cout << a.first  << " " << a.second << endl;

  return 0;
}