#include <iostream>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

int main (){
  multimap<string,string> my_mulmap;
  //my_mulmap["Johnny"s]; apparently for mulpimap this is impossible..

  auto ret = my_mulmap.insert({"Leerooooooooooy","Jeeeeenkiiiins" });
  ret = my_mulmap.insert({"Leerooooooooooy","Jeeeeenkiiiins" });
  // interesting, here in multimap it returns iterator to the pair... hmm
  // se we cannot just see if the operation was successful or not..
  
  my_mulmap.insert({"Leerooooooooooy","Jeeeeenkiiiins" });
  my_mulmap.insert({"Leerooooooooooy","Jeeeeenkiiiins" });
  my_mulmap.insert({"Leerooooooooooy","Jeeeeenkiiiins" });

  /**
   * In the output there will be 5 times same value...
   * So in the multimap we may have even same relations.
   * And for now it negates even negation rules in DML
   */
  for (const auto &a : my_mulmap)
    cout << a.first + " " + a.second << endl;

  cout << setfill('-') << setw(50) << "" << endl;

  for ( auto &a : my_mulmap){
    if ( a.second == "Jeeeeenkiiiins" )
      a.second = "Lee";                              
    cout << a.first + " " + a.second << endl;
  }

  cout << setfill('-') << setw(50) << "" << endl;

  my_mulmap.insert({"Daddy","Cool" });
  my_mulmap.insert({"Zero","Sugar" });


  auto iter = my_mulmap.find("Leerooooooooooy");
  iter --;
  cout << iter->first + " " + iter->second << endl;
  iter ++;

  size_t size = my_mulmap.count ("Leerooooooooooy");

  for ( size_t i = 0; i < size; i ++ ){
    cout << iter->first + " " + iter->second << endl;
    iter ++;
  }

  cout << setfill('-') << setw(50) << "" << endl;
  
  my_mulmap.insert({"John","Christescu" });
  my_mulmap.insert({"John","Kovalski" });
  my_mulmap.insert({"John","Saskie" });
  my_mulmap.insert({"John","Wick" });
  /**
   * The second iterator is the next after the actually last.
   */
  auto iters = my_mulmap.equal_range("John");
  cout << iters.first->first  + " "  + iters.first->second << endl;
  cout << (--iters.second)->first  + " "  + (--iters.second)->second << endl;
  


  return 0;
}