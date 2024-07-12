// #PRIOR_NO
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

#include "CSupermarket.h"
#include "CDate.h"

struct TTester {
  static void test_1_store (){
    cout << "test_1_store - START" << endl;
    cout << "test_1_store - OK" << endl;
  }
  static void test_2_match (){
    cout << "test_2_match - START" << endl;
    CSupermarket s;
    assert (s.notExactMatch("Cake","Coke"));
    assert (s.notExactMatch("Cake","Cake"));
    assert (s.notExactMatch("Cake","cake"));
    assert (!s.notExactMatch("Cake","coke"));
    assert (s.notExactMatch("Cake","Caks"));

    cout << "test_2_match - END" << endl;
  }
  static void test_3_match (){
    CSupermarket s0;
    s0 . store ( "cccc", CDate ( 2016, 4, 30 ), 100 )
      . store ( "ccccc", CDate ( 2016, 4, 30 ), 100 )
      . store ( "ccccc", CDate ( 2016, 4, 30 ), 100 )
      . store ( "ccccc", CDate ( 2016, 4, 30 ), 100 );
  }
};

// #EX_END
