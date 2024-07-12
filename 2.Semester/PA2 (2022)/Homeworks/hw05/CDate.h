// #PRIOR_2
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

// #EX_END

class CDate
{
  public:
    CDate (uint Y, uint M, uint D);
    friend bool operator< (const CDate &lhs, const CDate &rhs);
    friend bool operator== (const CDate &lhs, const CDate &rhs);
    friend ostream &operator<< (ostream &os, const CDate &rhs);
    uint m_Y, m_M, m_D;

    // #EX_BEGIN
    friend struct TTester;
    // #EX_END
    
};
