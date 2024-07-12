// #PRIOR_1
// #EX_BEGIN
#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
//own
// #EX_END
template<typename T>
class CSharedPtr {
  public:
    CSharedPtr();
    ~CSharedPtr();
    CSharedPtr(const CSharedPtr &src);
    CSharedPtr &operator= (const CSharedPtr &rhs);
    bool operator== (const CSharedPtr &rhs) const;
    bool operator!= (const CSharedPtr &rhs) const;
    CSharedPtr(T *);

    T &operator* () const ;
    T * operator-> () const ;


    T * get() const;
    bool unique() const;
    uint32_t use_count() const;

    template<typename Type>
    friend CSharedPtr make_Shared ( const Type & );

    template<typename Type>
    friend CSharedPtr make_Shared ();


    void move (CSharedPtr src);
  private:
    T * m_Ps;
    uint32_t * m_Use;
    int index = 0;
    // #EX_BEGIN
    friend struct TTester;
    // #EX_END
};
    // #EX_BEGIN
#include "CSharedPtr.inl"
    // #EX_END
    