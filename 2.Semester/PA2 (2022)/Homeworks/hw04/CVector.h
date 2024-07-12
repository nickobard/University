// #PRIOR_2
// #EX_BEGIN
#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
// #EX_END
/**
 * @brief Class that represents dynamic allocation
 * of bytes as in vector conainer.
 * 
 */
class CVector{
  public:
  /// Constructor
    CVector () ;
  /// Destructor
    ~CVector () ;
  /// Copy constructor
    CVector ( const CVector &src ) ;
  /// Copy-assignment operator
    CVector &operator= ( const CVector &src ) ;
    uint8_t & operator [] (const uint32_t pos ) ;

    void PushBack ( uint8_t val ) ;
    bool Empty () const ;
    uint32_t Size () const ;
    uint32_t MaxSize () const ;
    void ShrinkToFit();
    void ShrinkToFit( uint32_t pos );
    void move(CVector src);
// #EX_BEGIN
    void print () const ;
// #EX_END
  private:
    uint8_t * m_Data;
    uint32_t m_Cap;
    uint32_t m_Used;
// #EX_BEGIN
    friend struct TTester;
// #EX_END
};