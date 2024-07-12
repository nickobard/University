// #PRIOR_4
// #EX_BEGIN
#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;

#include "CDate.h"


// #EX_END

class CSupermarket
{
  public:
    CSupermarket &store (const string &name,
                          const CDate  &date,
                          const int   count );
    CSupermarket &sell  (list<pair<string,int>> &orders);
    list<pair<string,int>> expired ( const CDate &date ) const;
  private:
    void catCounters ( list<pair<string,int>> &expired ) const;
    static bool notExactMatch(const string &lhs,
                              const string &rhs );

    pair<string,bool> notExactSearch (const string &str) const;
    void processTransaction(list<pair<string,int>> &orders,
                            list<pair<string,int>>::iterator &order,
                            const string &key) ;
    map<string,map<CDate,shared_ptr<int>>> m_Trade;
    map<CDate,unordered_map<string,shared_ptr<int>>> m_Expire;
    unordered_map<size_t,unordered_set<string>> m_Names;
    // #EX_BEGIN
    friend struct TTester;
    // #EX_END

};
