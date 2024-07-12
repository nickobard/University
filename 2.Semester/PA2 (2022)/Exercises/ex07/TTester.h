//  #EX_BEGIN
//  #PRIOR_NO
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
#include "CEFaceMask.h"
#include "CContact.h"

struct TTester {

  static void test_old(){
/*
    CEFaceMask test;
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) )
        . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
    assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
    assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
*/
  } 
  static void test_1(){
    CEFaceMask test;
    test.addContact(CContact(CTimeStamp(2021,1,1,10,00,00),1,2));
    test.addContact(CContact(CTimeStamp(2022,1,1,10,00,00),3,2));
    test.addContact(CContact(CTimeStamp(2023,1,1,10,00,00),2,4));
    test.addContact(CContact(CTimeStamp(2023,1,1,10,00,00),2,4));
    test.addContact(CContact(CTimeStamp(2023,1,1,10,00,00),2,4));
    test.addContact(CContact(CTimeStamp(2023,1,1,10,00,00),4,2));
    test.addContact(CContact(CTimeStamp(2024,1,1,10,00,00),5,4));
    test.getSuperSpreaders(CTimeStamp(2022,1,1,10,00,00),
                           CTimeStamp(2023,1,1,10,00,00));

  }
};

//  #EX_END