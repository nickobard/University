/* __PROGT_BEGIN__ */
#pragma once
#include <cstring>
#include "CLinkedSetTester.h"
/* __PROGT_END__ */

/**
 * @brief My fisrt comment in doxygen. I am happy.
 * 
 */
class CLinkedSet
{
private:
    /// Look, here is another commentary
    struct CNode
    {
        CNode * m_Next;
        char  * m_Val ;
        const char * Value () const;
        ~CNode();
    };
    CNode * m_Begin;
    size_t m_Size;

public:
    // default constructor
    CLinkedSet();
    // copy constructor
    CLinkedSet(const CLinkedSet &cp);
    // operator=
    CLinkedSet &operator= (const CLinkedSet &rhs);
    // destructor
    ~CLinkedSet();

    /* __PROGT_BEGIN__ */
    // display
    void print() const;
    /* __PROGT_END__ */
    /**
     * @brief This functions inserts c-style string
     * 
     * @param value - c-style string to insert into set
     * @return true - if value is unique and inserted
     * @return false - if value already is in the set
     */
    bool Insert ( const char * value );
    
    bool Remove ( const char * value );

    bool Empty () const;

    size_t Size () const;

    bool Contains ( const char * value ) const;

    friend class ::CLinkedSetTester;
};