#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

//  #IN_SRC

//  #EX_BEGIN
class CFile
{
  public:
                             CFile                         ( void );
                             // copy cons, dtor, op=
    bool                     seek                          ( uint32_t          offset );
    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes );
    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes );
    void                     truncate                      ( void );
    uint32_t                 fileSize                      ( void ) const;
    void                     addVersion                    ( void );
    bool                     undoVersion                   ( void );
  private:
    // todo
};

//  #EX_END
#ifndef __PROGTEST__
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
int main ( void )
{
  CFile f0;

  assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
  assert ( f0 . fileSize () == 3 );
  assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 2 ));
  assert ( writeTest ( f0, { 5, 4 }, 2 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 1 ));
  assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));
  assert ( f0 . seek ( 3 ));
  f0 . addVersion();
  assert ( f0 . seek ( 6 ));
  assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );
  f0 . addVersion();
  assert ( f0 . seek ( 5 ));
  CFile f1 ( f0 );
  f0 . truncate ();
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
  assert ( !f0 . seek ( 100 ));
  assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
  assert ( f1 . seek ( 0 ));
  assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
  assert ( f1 . undoVersion () );
  assert ( f1 . undoVersion () );
  assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
  assert ( !f1 . undoVersion () );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
