// #PRIOR_3
// #EX_BEGIN
#pragma once 
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
//own
#include "CSharedPtr.h"
#include "CVector.h"
// #EX_END

/**
 * @struct TFile
 * @brief Struct which represents each File instance.
 * 
 * It uses synthesized copy control, because all its members
 * provide own copy control.
 * 
 */
struct TFile {
  /**
   * @brief User default constructor.
   * 
   * m_Pos is initialized with 0.
   * 
   * m_Data is initialized with self constructor.
   */
  TFile ()
  : p_Data(make_Shared<CVector>())
  , m_Pos(0)
  {}

  TFile (const TFile &src) = default;
  TFile &operator= (const TFile &rhs) = default ;

  /**
   * @brief Special constructor for deep copy
   * 
   * @param new_data - deep copied 
   * @param pos 
   */
  CSharedPtr<CVector> p_Data; 
  uint32_t m_Pos; ///< Stores last position in this file
};