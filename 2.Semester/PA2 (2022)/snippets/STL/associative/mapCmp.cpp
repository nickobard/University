#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

struct TCmp{
  
  bool operator()(const pair<string, int> &lhs,
                  const pair<string, int> &rhs ){
                    return lhs < rhs;
  }
  bool operator()(const string &rhs,
                  const pair<string, int> &lhs
                   ){
                    return lhs.first < rhs;
  }
};

int main (){

  map<pair<string, int>, int, TCmp> umap;

  umap.insert({{"Bread",2020},10});
  umap.insert({{"Bread",2021},10});
  umap.insert({{"Bread",2016},10});
  umap.insert({{"Bread",2018},10});
  umap.insert({{"Bread",2019},10});
  umap.insert({{"Bread",2017},10});

  for_each(umap.cbegin(),umap.cend(),[&]
  (const map<pair<string, int>, int, TCmp>::value_type &el)
  {cout << el.first.first << " " << el.first.second << " " << el.second << endl;});

  string str = "Bread";
  umap.lower_bound(str);




  
  return 0;
}