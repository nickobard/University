//  #EX_BEGIN
//  #PRIOR_6
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

#include "CContact.h"
//  #EX_END

class CEFaceMask
{
  public:
    // default constructor
    // addContact ( contact )
    CEFaceMask &addContact( const CContact &contact );
    // getSuperSpreaders ( from, to )
    vector<int> getSuperSpreaders ( const CTimeStamp &from,
                                    const CTimeStamp &to );
  private:
    void getSorted(vector<CContact> &src) const;
    void getUnique(vector<CContact> &src) const;
    vector<CContact> getContactsFromRange(const CTimeStamp &from,
                                          const CTimeStamp &to ) const;
    map<int,int> getSpreaders (vector<CContact> &src) const;
    vector<CContact> m_Contacts;
    
    //  #EX_BEGIN
    friend struct TTester;
    //  #EX_END

};