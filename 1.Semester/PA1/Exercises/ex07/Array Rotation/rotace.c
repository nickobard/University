#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

void rotateArray ( int array [], int arrayLen, int rotateBy )
{
  /* TODO: Your code here */
  int tmp ;
  int lastEl = arrayLen - 1 ;
  
  // Skip full circles, e.g. len = 9, rotate = -100, it is enough to shift just one time to left ( -100 % 9 ) = -1
  rotateBy %= arrayLen ;
  
  /**
   * Check if it is more effective to shift from other side.
   *
   * e.g. rotateBy = -9 , arrayLen = 12.
   * it will be faster to check, if |rotateBy| > 12 / 2 = 6.
   * if yes, less steps will be taking shifting from other side.
   * then rotateBy = -9 + 12 = 3 times from left to right. -> time saved.
   */
  if ( rotateBy < 0 )
  	{
  		if ( -rotateBy > arrayLen / 2 ) rotateBy += arrayLen ;
  	}
  else if ( rotateBy > 0 )
  	{
  		if ( rotateBy > arrayLen / 2 ) rotateBy -= arrayLen ;
  	}
  
  /**
   * Save last or fist elements to tmp, because it will be lost while shifting.
   * then for rotateBy x times, shift every element in the specified before direction by one position.
   */
  
  if ( rotateBy > 0 )
  {
  	for ( int i = 0 ; i < rotateBy ; i ++ )
  	{ 
  		tmp = array [ lastEl ] ;
	  	for ( int i = lastEl ; i > 0  ; i-- )
	  	{
	  		array [ i ] = array [ i - 1 ] ;
	  	} 
	  	array [ 0 ] = tmp ;
	}
  }
  else if ( rotateBy < 0 )
  {
  	for ( int i = 0 ; i < -rotateBy ; i ++ )
  	{ 
  		tmp = array [ 0 ] ;
	  	for ( int i = 0 ; i < lastEl ; i++ )
	  	{
	  		array [ i ] = array [ i + 1 ] ;
	  	} 
	  	array [ lastEl ] = tmp ;
	}
  
  }
}

#ifndef __PROGTEST__
int identicalArrays ( const int a[], const int b[], int cnt )
{
  /* TODO: Your code here */
  
  for ( int i = 0 ; i < cnt ; i++ )
  	{
  	if ( a [ i ] != b [ i ] )
  		return 0 ;
  	}
  return 1 ;
  
}
int main (int argc, char * argv [])
{
  int in0 []  = { 1, 2, 3, 4, 5 };
  int out0 [] = { 5, 1, 2, 3, 4 };

  int in1 []  = { 1, 2, 3, 4, 5 };
  int out1 [] = { 2, 3, 4, 5, 1 };

  int in2 []  = { 1, 2, 3, 4, 5, 6 };
  int out2 [] = { 4, 5, 6, 1, 2, 3 };

  int in3 []  = { 1, 2, 3, 4, 5, 6, 7 };
  int out3 [] = { 3, 4, 5, 6, 7, 1, 2 };

  int in4 []  = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int out4 [] = { 2, 3, 4, 5, 6, 7, 8, 9, 1 };

  rotateArray ( in0, 5, 1 );
  assert ( identicalArrays ( in0, out0, 5 ) );
  rotateArray ( in1, 5, -1 );
  assert ( identicalArrays ( in1, out1, 5 ) );
  rotateArray ( in2, 6, -3 );
  assert ( identicalArrays ( in2, out2, 6 ) );
  rotateArray ( in3, 7, 12 );
  assert ( identicalArrays ( in3, out3, 7 ) );
  rotateArray ( in4, 9, -100 );
  assert ( identicalArrays ( in4, out4, 9 ) );
  return 0;
}
#endif /* __PROGTEST__ */

