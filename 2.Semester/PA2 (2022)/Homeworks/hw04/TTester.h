// #PRIOR_NO
// #EX_BEGIN
// PROGTEST
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
// OWN
#include "TFile.h"
#include "CFile.h"
#include "CVector.h"
#include "CStack.h"
#include "CSharedPtr.h"
#include <memory>


bool               writeTest                               ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          wrLen )
{
  return x . write ( data . begin (), data . size () ) == wrLen;
}

bool               readTest                                ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          rdLen )
{
  uint8_t  tmp[100];
  uint32_t idx = 0;

  if ( x . read ( tmp, rdLen ) != data . size ())
    return false;
  for ( auto v : data )
    if ( tmp[idx++] != v )
      return false;
  return true;
}

/**
 * @brief Struct to test units.
 * 
 */
struct TTester
{
  static void test0(){
    cout << "test0 -> START" << endl;
    // test
    CVector vec1;
    for ( uint8_t i = 1; i <= 105; i++){
      vec1.PushBack(i); 
    }
    //vec1.print();
    for ( uint8_t i = 1; i <= 105; i++){
      assert (vec1[i-1] == i);
    }
    for ( uint8_t i = 105; i > 0 ; i--){
      assert (vec1[i-1] = i);
    }
    for ( uint8_t i = 105; i > 0; i--){
      assert (vec1[i-1] == i);
    }
    CVector v2 (vec1);
    CVector v3 (vec1);
    for ( uint32_t i = 0; i < v2.Size(); i++){
      assert (v2[i] == v3[i]);
    }
    assert (vec1.Size() ==  105);
    assert (vec1.MaxSize() !=  105);
    vec1.ShrinkToFit();
    assert (vec1.Size() ==  105);
    assert (vec1.MaxSize() ==  105);

    for ( uint8_t i = 1; i <= 200; i++){
      vec1.PushBack(i); 
    }

    vec1.ShrinkToFit(0);
    assert (vec1.Empty());
    vec1.PushBack(69);
    assert (vec1.Size() == 1 );
    assert (vec1.MaxSize() == 100);

    CVector v0, v1;
    v0 = v1;
    assert (v0.Empty());
    assert (v1.Empty());

    cout << "test0 -> OK" << endl;
  }
    /*cout << "test_1_cstack -> START" << endl;
  static void test_1_cstack(){
    CStack x0;
    TFile  f0;
    f0.m_Pos = 1; x0.Push( f0 );
    f0.m_Pos = 2; x0.Push( f0 );
    f0.m_Pos = 3; x0.Push( f0 );
    f0.m_Pos = 4; x0.Push( f0 );
    f0.m_Pos = 5; x0.Push( f0 );
    f0.m_Pos = 1; x0.Push( f0 );
    f0.m_Pos = 2; x0.Push( f0 );
    f0.m_Pos = 3; x0.Push( f0 );
    f0.m_Pos = 4; x0.Push( f0 );
    f0.m_Pos = 5; x0.Push( f0 );
    f0.m_Pos = 1; x0.Push( f0 );
    f0.m_Pos = 2; x0.Push( f0 );
    f0.m_Pos = 3; x0.Push( f0 );
    f0.m_Pos = 4; x0.Push( f0 );
    f0.m_Pos = 5; x0.Push( f0 );

    CStack x1;
    x1 = x0;
    assert (x1.Size() == 15); 

    for ( int i = 0; i < 3; i++){
      assert (x1.Top().m_Pos == 5); assert (x1.Pop());
      assert (x1.Top().m_Pos == 4); assert (x1.Pop());
      assert (x1.Top().m_Pos == 3); assert (x1.Pop());
      assert (x1.Top().m_Pos == 2); assert (x1.Pop());
      assert (x1.Top().m_Pos == 1); assert (x1.Pop());
    }
      assert (x1.Empty());
      assert (!x0.Empty());

    for ( int i = 0; i < 3; i++){
      assert (x0.Top().m_Pos == 5); assert (x0.Pop());
      assert (x0.Top().m_Pos == 4); assert (x0.Pop());
      assert (x0.Top().m_Pos == 3); assert (x0.Pop());
      assert (x0.Top().m_Pos == 2); assert (x0.Pop());
      assert (x0.Top().m_Pos == 1); assert (x0.Pop());
    }
      assert (x1.Empty());
      assert (x0.Empty());
    x1 = x0;
      assert (x1.Empty());
      assert (x0.Empty());
      assert (x0.Size() == 0); 
      assert (x1.Size() == 0); 


    for ( int i = 0; i < 3; i++){
      f0.m_Pos = 1; x0.Push( f0 );
      f0.m_Pos = 2; x0.Push( f0 );
      f0.m_Pos = 3; x0.Push( f0 );
      f0.m_Pos = 4; x0.Push( f0 );
      f0.m_Pos = 5; x0.Push( f0 );
    }
     for ( int i = 0; i < 4; i++){
      f0.m_Pos = 1; x1.Push( f0 );
      f0.m_Pos = 2; x1.Push( f0 );
      f0.m_Pos = 3; x1.Push( f0 );
      f0.m_Pos = 4; x1.Push( f0 );
      f0.m_Pos = 5; x1.Push( f0 );
    } 
    assert (x0.Size() == 15);
    assert (x1.Size() == 20); 

    CStack tmp;
    tmp = x0;
    assert (tmp.Size() == 15);
    x0 = x1;
    x1 = tmp;

    assert (x1.Size() == 15);
    assert (x0.Size() == 20); 

    x0 = x0;
    x1 = x1;

    assert (x1.Size() == 15);
    assert (x0.Size() == 20); 

  for ( int i = 0; i < 4; i++){
      assert (x0.Top().m_Pos == 5); assert (x0.Pop());
      assert (x0.Top().m_Pos == 4); assert (x0.Pop());
      assert (x0.Top().m_Pos == 3); assert (x0.Pop());
      assert (x0.Top().m_Pos == 2); assert (x0.Pop());
      assert (x0.Top().m_Pos == 1); assert (x0.Pop());
    }

      for ( int i = 0; i < 3; i++){
      assert (x1.Top().m_Pos == 5); assert (x1.Pop());
      assert (x1.Top().m_Pos == 4); assert (x1.Pop());
      assert (x1.Top().m_Pos == 3); assert (x1.Pop());
      assert (x1.Top().m_Pos == 2); assert (x1.Pop());
      assert (x1.Top().m_Pos == 1); assert (x1.Pop());
    }
    assert (x1.Size() == 0);
    assert (x0.Size() == 0);

    assert (x1.Empty());
    assert (x0.Empty());

    cout << "test_1_cstack -> OK" << endl;
  }
    */
  /*
  static void test_2_shared(){
    cout << "test_2_shared -> START" << endl;

    TFile f0, f1; 
    assert (f0.p_Data->Empty());
    assert (f1.p_Data->Empty());
    f1 = f0; 
    assert (f0.p_Data->Empty());
    assert (f1.p_Data->Empty());
    f0.p_Data->PushBack(42);
    assert (f1.p_Data->Empty());
    assert (!f0.p_Data->Empty());
    f1.p_Data->PushBack(69);
    f1.p_Data->PushBack(69);
    assert ((*f0.p_Data)[0] == 42);
    assert ((*f1.p_Data)[0] == 69);
    assert ((*f1.p_Data)[1] == 69);
    assert (f0.p_Data->Size() == 1);
    assert (f1.p_Data->Size() == 2);

    TFile f2(f1);

    (*f2.p_Data)[0] = 42;
    (*f2.p_Data)[1] = 42;
    assert ((*f1.p_Data)[0] == 69);
    assert ((*f1.p_Data)[1] == 69);
    assert ((*f2.p_Data)[0] == 42);
    assert ((*f2.p_Data)[1] == 42);

    cout << "test_2_shared -> OK" << endl;

  }
  static void test_3_shared(){
    cout << "test_3_shared -> START" << endl;

    CStack s0;
    TFile f0;
    f0.p_Data->PushBack(69);
    f0.m_Pos = 1;
    s0.PushShared(f0);
    f0.m_Pos = 2;
    s0.PushShared(f0);
    f0.m_Pos = 3;
    s0.PushShared(f0);

    f0.p_Data = make_Shared<CVector>(*f0.p_Data);
    f0.p_Data->PushBack(42);
    f0.p_Data->PushBack(41);
    f0.p_Data->PushBack(14);
    f0.p_Data->PushBack(66);
    f0.m_Pos = 4;

    s0.PushShared(f0);
    f0.m_Pos = 5;
    
    assert(s0.m_Top->m_File.p_Data == f0.p_Data);
    assert(s0.m_Top->m_File.m_Pos == 4);
    assert(s0.m_Top->m_File.m_Pos != f0.m_Pos);

    assert(s0.m_Size == 4);

    assert(s0.m_Top->m_next->m_File.p_Data != f0.p_Data);
    assert(s0.m_Top->m_next->m_File.m_Pos == 3);
    assert(s0.m_Top->m_next->m_File.p_Data 
        == s0.m_Top->m_next->m_next->m_File.p_Data );
    assert(s0.m_Top->m_next->m_File.p_Data 
        == s0.m_Top->m_next->m_next->m_next->m_File.p_Data );
    

    assert (s0.m_Top->m_File.p_Data->Size()== 5);
    assert((*s0.m_Top->m_File.p_Data)[0] == 69);

    assert (s0.m_Top->m_next->m_File.p_Data->Size()== 1);
    assert (s0.m_Top->m_next->m_next->m_File.p_Data->Size()== 1);
    assert (s0.m_Top->m_next->m_next->m_next->m_File.p_Data->Size()== 1);
    assert((*s0.m_Top->m_next->m_File.p_Data)[0] == 69);
    assert((*s0.m_Top->m_next->m_next->m_File.p_Data)[0] == 69);
    assert((*s0.m_Top->m_next->m_next->m_next->m_File.p_Data)[0] == 69);

    assert((*s0.m_Top->m_File.p_Data)[0] == 69);

    (*s0.m_Top->m_next->m_next->m_next->m_File.p_Data)[0] = 14;

    assert((*s0.m_Top->m_next->m_File.p_Data)[0] == 14);
    assert((*s0.m_Top->m_next->m_next->m_File.p_Data)[0] == 14);
    assert((*s0.m_Top->m_next->m_next->m_next->m_File.p_Data)[0] == 14);

    cout << "test_3_shared -> OK" << endl;
  }
  */

  /*
  static void test_4_sh_copy(){
    cout << "test_4_sh_copy -> START" << endl;

    CStack s0;

    TFile f0;
    f0.p_Data->PushBack(69);
    f0.m_Pos = 1;
    s0.PushShared(f0);
    f0.m_Pos = 2;
    s0.PushShared(f0);
    f0.m_Pos = 3;
    s0.PushShared(f0);
    assert (s0.m_Top->m_File.p_Data == s0.m_Top->m_next->m_File.p_Data);
    assert (s0.m_Top->m_File.p_Data == s0.m_Top->m_next->m_next->m_File.p_Data);

    CStack s1;
    s1 = s0;
    assert (s0.m_Top->m_File.p_Data != s1.m_Top->m_File.p_Data);
    assert (s0.m_Top->m_next->m_File.p_Data != s1.m_Top->m_next->m_File.p_Data);
    assert (s0.m_Top->m_next->m_next->m_File.p_Data != s1.m_Top->m_next->m_next->m_File.p_Data);

    assert (s1.m_Top->m_File.p_Data == s1.m_Top->m_next->m_File.p_Data);
    assert (s1.m_Top->m_File.p_Data == s1.m_Top->m_next->m_next->m_File.p_Data);
    cout << "test_4_sh_copy -> OK" << endl;
  } 
  */ 
  static void test_5_sh_own(){
    cout << "test_5_sh_own -> START" << endl;
    typedef int dummy;
    CSharedPtr<dummy> p0, p1;
    p0 = p1;
    p0 = p0;
    p1 = p1;

    assert(p0.m_Ps == nullptr);
    assert(p0.m_Use == nullptr);

    CSharedPtr<dummy> p2 (new dummy(42));
    p0 = p2;
    p1 = p2;
    assert (*p0.m_Use == 3);
    assert (*p1.m_Use == 3);
    assert (*p2.m_Use == 3);

    CSharedPtr<dummy> p3 (new dummy(69));
    p0 = p3;
    assert (*p2.m_Use == 2);
    assert (*p3.m_Use == 2);

    CSharedPtr<dummy> p4 (p3);
    
    assert (*p3.m_Use == 3);
    CSharedPtr<dummy> p5;
    p0 = p5;
    p1 = p5;
    p2 = p5;
    p3 = p5;
    p4 = p5;

    assert (p5.m_Use == 0);
    assert (p4.m_Use == 0);
    assert (p3.m_Use == 0);
    assert (p2.m_Use == 0);
    assert (p1.m_Use == 0);
    assert (p0.m_Use == 0);


    p0 = make_Shared<dummy>(62);
    p0 = make_Shared<dummy>(42);
    p0 = make_Shared<dummy>(62);
    p0 = make_Shared<dummy>(42);
    p0 = make_Shared<dummy>(62);
    assert ( *p0.m_Use == 1 );
    assert ( *p0.m_Ps == 62 );

    dummy * pd0 = p0.get();
    *pd0 = 42;

    assert ( *p0.m_Use == 1 );
    assert ( *p0.m_Ps == 42 );

    // test how is expected
    //shared_ptr<dummy> lsp0;
    //cout << lsp0.use_count() << endl; // 0
    //cout << boolalpha << (lsp0.get() == nullptr) << endl; // true
    //cout << boolalpha <<  lsp0.unique() << endl; // false

    CSharedPtr<dummy> p6;
    assert(p6.unique() == false);
    assert(p6.get() == nullptr);
    assert(p6.use_count() == 0);

    assert(p0.unique() == true);
    assert(p0.get() != nullptr);
    assert(p0.use_count() == 1);

    p6 = p0;
    assert(p6.unique() == false);
    assert(p6.get() != nullptr);
    assert(p6.use_count() == 2);
    p5 = p0;
    assert(p6.unique() == false);
    assert(p6.get() != nullptr);
    assert(p6.use_count() == 3);

    assert(*p6 == 42);

    CSharedPtr<CVector> vec1 (new CVector());
    assert(vec1.unique() == true);
    assert(vec1.use_count() == 1);
    assert(vec1.get() != nullptr );

    shared_ptr<CVector> vec2 (new CVector());
    //cout << vec1.use_count() << endl; // 1
    //cout << vec2.use_count() << endl; // 1
    assert(vec2.unique() == true);
    assert(vec2.use_count() == 1);
    assert(vec2.get() != nullptr );

    (*vec1).PushBack(42);
    (*vec2).PushBack(69);

    assert(vec1->Size() == 1);
    vec1->PushBack(42);
    assert(vec1->Size() == 2);

    vec1->m_Used = 10;
    assert(vec1->Size() == 10);

    CSharedPtr<CVector> v3(make_Shared<CVector>());


    cout << "test_5_sh_own -> OK" << endl;
  }
  /*
  static void test_6_cfile(){
    cout << "test_6_cfile -> START" << endl;
    CFile f0;
    assert (writeTest(f0,{1,2,3,4,5},5));
    assert (writeTest(f0,{1,2,3,4,5},5));
    assert (writeTest(f0,{1,2,3,4,5},5));
    f0.truncate();
    f0.addVersion();
    f0.truncate();
    f0.truncate();
    f0.addVersion();
    f0.addVersion();
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (!f0.undoVersion());
    assert (!f0.undoVersion());
    assert (!f0.undoVersion());

    assert (f0.seek(0));
    //f0.m_File.p_Data->print();
    f0.truncate();
    //f0.m_File.p_Data->print();
    f0.addVersion();
    f0.addVersion();
    f0.addVersion();
    f0.addVersion();
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (!f0.undoVersion());

    
    f0.addVersion();
    f0.addVersion();
    
    assert (writeTest(f0,{1,2,3,4,5},5));
    f0.addVersion();
    assert (writeTest(f0,{1,2,3,4,5},5));
    f0.addVersion();
    assert (writeTest(f0,{1,2,3,4,5},5));
    f0.addVersion();
    assert (writeTest(f0,{1,2,3,4,5},5));
    f0.addVersion();
    cout << "test_6_cfile -> END" << endl;
  }
  static void test_6_cfile_copy(){
    cout << "test_6_cfile_copy -> START" << endl;
    CFile f0;
    CFile f1;
    f0 = f1;
    f0 = f0;
    f1 = f1;
    f0.addVersion();
    f0.addVersion();
    f0.addVersion();
    f1 = f0;
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (f0.undoVersion());
    assert (!f0.undoVersion());
    
    assert (f1.undoVersion());
    assert (f1.undoVersion());
    assert (f1.undoVersion());
    assert (!f1.undoVersion());

    CFile f3;
    writeTest(f3,{1,2,3},3);
    f3.addVersion();
    writeTest(f3,{},0);
    assert(f3.m_File.p_Data == f3.m_Versions.getTop().p_Data);

    CFile f4(f3);
    assert(f4.m_File.p_Data == f4.m_Versions.m_Top->m_File.p_Data);
    f4 = f3;
    assert(f4.m_File.p_Data == f4.m_Versions.m_Top->m_File.p_Data);

    CFile f5;
    writeTest(f5,{1,2,3},3);
    f5.addVersion();
    f5.addVersion();
    f5.addVersion();
    writeTest(f5,{1,2,3},3);
    f5.addVersion();
    f5.addVersion();

    CFile f6 = f5;
    assert(f5.m_File.p_Data == f5.m_Versions.m_Top->m_File.p_Data);
    assert(f5.m_Versions.m_Top->m_File.p_Data == f5.m_Versions.m_Top->m_next->m_File.p_Data);

    assert(! (f5.m_Versions.m_Top->m_next->m_File.p_Data == f5.m_Versions.m_Top->m_next->m_next->m_File.p_Data));

    assert(f5.m_Versions.m_Top->m_next->m_next->m_File.p_Data == f5.m_Versions.m_Top->m_next->m_next->m_next->m_File.p_Data);
    assert(f5.m_Versions.m_Top->m_next->m_next->m_next->m_File.p_Data == f5.m_Versions.m_Top->m_next->m_next->m_next->m_next->m_File.p_Data);



    assert(f6.m_File.p_Data == f6.m_Versions.m_Top->m_File.p_Data);
    assert(f6.m_Versions.m_Top->m_File.p_Data == f6.m_Versions.m_Top->m_next->m_File.p_Data);

    assert(! (f6.m_Versions.m_Top->m_next->m_File.p_Data == f6.m_Versions.m_Top->m_next->m_next->m_File.p_Data));

    assert(f6.m_Versions.m_Top->m_next->m_next->m_File.p_Data == f6.m_Versions.m_Top->m_next->m_next->m_next->m_File.p_Data);
    assert(f6.m_Versions.m_Top->m_next->m_next->m_next->m_File.p_Data == f6.m_Versions.m_Top->m_next->m_next->m_next->m_next->m_File.p_Data);
    

    cout << "test_6_cfile_copy -> OK" << endl;
  }
  */
};

// #EX_END