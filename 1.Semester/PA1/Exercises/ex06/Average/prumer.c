#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "gen_func.h"
#endif /* __PROGTEST__ */

long long avg3 ( long long a, long long b, long long c )
{
  /* TODO: Your code here */
 long long remainder = 0, average = 0;
 
 remainder = ( a % 3 ) + ( b % 3 ) + ( c % 3 ) ;
 average = a/3 + b/3 + c/3 ;
 average += remainder/3 ;
 /** 
  * We should solve cases when -10 + 1/3 must be -9, not -10
  * but on the other hand -10 - 1/3 will be -10 1/3 , should be just -10
  *
  * Indetically with positive numbers, when 10 - 1/3 should be 9 2/3 -> 9
  * and 10 + 1/3 = 10 1/3 -> 10.
  * 
  * Both situations doesn work with 0, becase 0 +/- 1/3 = 0.
  * Therefore the average should be equal to 0 in both conditions.
  */
 if ( remainder % 3 < 0 && average > 0 ) average -= 1 ;
 else if ( remainder % 3 > 0 && average < 0 ) average += 1 ;
 return average;
}

#ifndef __PROGTEST__
void genTest ( int tests_nr , int size_nr , int offset , int test_msg_on , int time_rand, int seed ) ;
#endif /* __PROGTEST__ */

#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
/*---------------------------MY-ADDED--------------------------------------*/
assert ( avg3 ( 3, -1, -3 ) == 0 ) ;
assert ( avg3 ( 2, -1, -2 ) == 0 ) ;
assert ( avg3 ( 3, -1, 3 ) == 1 ) ;
assert ( avg3 ( 2, -1, 2 ) == 1 ) ;
assert ( avg3 ( 0, -5, 4 ) == 0 ) ;


/*---------------------------RANDOMLY-GENERATED----------------------------*/

assert ( avg3 ( 83, -14, 77 ) == 48 ) ;
assert ( avg3 ( 15, 93, 35 ) == 47 ) ;
assert ( avg3 ( 86, -8, -51 ) == 9 ) ;
assert ( avg3 ( -79, 62, -73 ) == -30 ) ;
assert ( avg3 ( -10, -41, 63 ) == 4 ) ;
assert ( avg3 ( 26, 40, -74 ) == -2 ) ;
assert ( avg3 ( 72, 36, -89 ) == 6 ) ;
assert ( avg3 ( 68, 67, -71 ) == 21 ) ;
assert ( avg3 ( 82, 30, -38 ) == 24 ) ;
assert ( avg3 ( 23, -33, 35 ) == 8 ) ;
assert ( avg3 ( 29, -98, -78 ) == -49 ) ;
assert ( avg3 ( -42, -31, 67 ) == -2 ) ;
assert ( avg3 ( 93, -44, -89 ) == -13 ) ;
assert ( avg3 ( -58, -71, 73 ) == -18 ) ;
assert ( avg3 ( -79, 19, 84 ) == 8 ) ;
assert ( avg3 ( 37, 98, 24 ) == 53 ) ;
assert ( avg3 ( 15, 70, -87 ) == 0 ) ;
assert ( avg3 ( 26, -9, 80 ) == 32 ) ;
assert ( avg3 ( 56, -27, -38 ) == -3 ) ;
assert ( avg3 ( 70, 96, -19 ) == 49 ) ;

/*---------------------------CALLED-FUNCTION-------------------------------*/

genTest ( 100 , 20 , 10 , 0 , 1 ) ;
genTest ( 100 , 10 , 5 , 0 , 1 ) ;

/*-------------------------------------------------------------------------*/
  assert ( avg3 ( -2, -2, 8 ) == 1 );
  assert ( avg3 ( 1, 2, 3 ) == 2 );
  assert ( avg3 ( -100, 100, 30 ) == 10 );
  assert ( avg3 ( 1, 2, 2 ) == 1 );
  assert ( avg3 ( -1, -2, -2 ) == -1 );
  assert ( avg3 ( LLONG_MAX, LLONG_MAX, LLONG_MAX ) == LLONG_MAX );
  return 0;
}
#endif /* __PROGTEST__ */

