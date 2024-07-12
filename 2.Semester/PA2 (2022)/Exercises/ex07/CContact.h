//  #EX_BEGIN
//  #PRIOR_4
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

#include "CTimeStamp.h"
//  #EX_END

class CContact
{
  public:
    // constructor ( timeStamp, phone1, phone2 )
    // TODO
    CContact ( const CTimeStamp &timestamp, int num1, int num2 );
    friend ostream &operator<< (ostream &, const CContact &);
    bool eqNums () const ;
  private:
    CTimeStamp m_Timestamp;
    pair <int, int> phones;
    friend class CEFaceMask;
    //  #EX_BEGIN
    friend struct TTester;
    //  #EX_END
};
