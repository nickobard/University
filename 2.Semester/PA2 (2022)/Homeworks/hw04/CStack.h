// #PRIOR_4
// #EX_BEGIN
#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
//own
#include "TFile.h"
// #EX_END
/**
 * @brief Class to store file versions.
 * 
 * Stores each TFile instance into the stack,
 * making full copy of it.
 * 
 */
class CStack {
  public:
    struct CNode {
      CNode * m_next;
      TFile m_File;
    };

    CStack ();
    ~CStack ();
    CStack (const CStack &src);
    CStack &operator= (const CStack &rhs);

    void Push(const TFile &version);
    bool Pop();
    TFile Top( ) const;
    bool Empty() const ;
    uint32_t Size() const ;
    void move(CStack src);
  private:
    CNode * m_Top;
    uint32_t m_Size;
    // #EX_BEGIN
    friend struct TTester;
    // #EX_END
};