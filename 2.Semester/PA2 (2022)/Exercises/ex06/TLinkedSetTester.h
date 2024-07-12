/* __PROGT_BEGIN__ */
#pragma once
#include <cassert>
#include "CLinkedSet.h"
#include <iostream>
using namespace std;

struct CLinkedSetTester
{
    static void test0()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        assert( !x0 . Empty() );
    }

    static void test1()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CLinkedSet x1 ( x0 );
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
        /*
        */
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        x1 = x0;
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

    static void test3()
    {
        CLinkedSet x0;
        x0.Insert("a");
        x0.Insert("a");
        x0.Insert("a");
        x0.Insert("a");
        x0.Insert("");
        x0.Insert("");
        x0.Insert("");
        x0.Insert("");
        assert ( x0.Size() == 2 );
        assert ( x0.Remove("a"));
        assert ( !x0.Remove("a"));
        assert ( !x0.Remove("a"));
        assert ( !x0.Remove("a"));
        assert ( !x0.Remove("a"));
        assert ( !x0.Remove("a"));
        assert ( !x0.Remove("a"));
        //x0.print(); 
        assert ( x0.Size() == 1 );
        assert(!x0.Contains("a"));
        assert(x0.Contains(""));
        assert(x0.Remove(""));
        assert(!x0.Remove(""));
        assert(!x0.Remove(""));
        assert(!x0.Remove(""));
        assert(!x0.Remove(""));
        assert(!x0.Remove(""));
        assert ( x0.Size() == 0 );
        assert(!x0.Contains("a"));
        assert(!x0.Contains(""));
        CLinkedSet x1;
        x1 = x0;
        assert(x0.Size() == 0);
        x0 = x1;
        assert (x1.Insert("b"));
        assert (x1.Insert("f"));
        assert (x1.Insert("d"));
        assert (x1.Insert("a"));
        assert (x1.Insert("e"));
        assert (x1.Insert("c"));
        assert (x0.Size() == 0);
        //x0.print();
        assert (x1.Size() == 6);
        CLinkedSet x3 (x1);
        assert (x3.Size() == 6);
        assert (x1.Remove("b"));
        assert (x1.Remove("f"));
        assert (x1.Remove("d"));
        //x1.print();
        assert (x1.Remove("a"));
        assert (x1.Remove("e"));
        assert (x1.Remove("c"));
        assert (x0.Size() == 0);
        assert (x3.Size() == 6);
        assert (x1.Size() == 0);
        //x3.print();

    }
};
/* __PROGT_END__ */