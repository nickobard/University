//  #EX_BEGIN
//  #PRIOR_2
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <cassert>
using namespace std;
//  #EX_END

class CTimeStamp
{
  public:
    // constructor ( y, m, d, h, min, s )
    // TODO
    CTimeStamp(int year, int month,   int day,
               int hour, int minutes, int seconds );
    CTimeStamp ( const CTimeStamp &src) = default;
    bool operator == (const CTimeStamp &rhs) const;
    bool operator != (const CTimeStamp &rhs) const;
    bool operator <  (const CTimeStamp &rhs) const;
    bool operator >  (const CTimeStamp &rhs) const;
    bool operator <= (const CTimeStamp &rhs) const;
    bool operator >= (const CTimeStamp &rhs) const;
    friend ostream &operator<< (ostream &os, const CTimeStamp &rhs);
  private:
    //members
    int c_year, c_month, c_day;
    int c_hour, c_minutes, c_seconds;

    //  #EX_BEGIN
    friend struct TTester;
    //  #EX_END

};