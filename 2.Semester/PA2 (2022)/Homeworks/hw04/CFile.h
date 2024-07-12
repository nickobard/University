// #PRIOR_5
// #EX_BEGIN
#pragma once
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
//own
#include "CStack.h"
#include "TFile.h"
// #EX_END
/**
 * @brief Class which represents file managment.
 * 
 */
class CFile
{
  public:
                             CFile                         ( void );
                             // copy cons, dtor, op=
                             CFile                         ( const CFile &src );
                            ~CFile                         ( void );
   CFile &                  operator=                     ( const CFile &rhs ); 

    bool                     seek                          ( uint32_t          offset );
    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes );
    /**
     * @brief Write bytes to m_File from the current position including byte at the current position.
     * 
     * @param src array of elements to write.
     * @param bytes how many bytes to write form the src array.
     * @return uint32_t number of written bytes, may be less if bytes < 
     * src size.
     */
    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes );
    /**
     * @brief Remove all elements from the current position and shrink data capacity to used.
     * 
     */
    void                     truncate                      ( void );
    /**
     * @brief Method to take actual size of the m_File.m_Data vector. 
     * 
     * @return uint32_t - how many bytes are written in m_File.m_Data.
     */
    uint32_t                 fileSize                      ( void ) const;
    /**
     * @brief Add version to the m_Versions stack.
     * 
     */
    void                     addVersion                    ( void );
    /**
     * @brief Retrieve last version from the top of the versions stack
     * 
     * Takes no parameters, but reassign m_File member to the previous version.
     * So the current m_File version will be lost.
     * 
     * @return true - if successfuly retrieved version.
     * @return false - if m_Versions is empty and cannot retrieve.
     */
    bool                     undoVersion                   ( void );
  private:
    // todo
    TFile m_File; //< Actual version of file.
    CStack  m_Versions; //< All previous versions.

    // #EX_BEGIN
    friend struct TTester;
    // #EX_END
};