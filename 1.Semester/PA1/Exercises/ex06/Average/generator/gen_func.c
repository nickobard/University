#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void genTest ( int tests_nr , int size_nr , int offset , int test_msg_on = 0 )
{
	for ( int i = 0 ; i < tests_nr ; i ++ )
	{
		int a = rand () % size_nr - offset ;
		int b = rand () % size_nr - offset ;
		int c = rand () % size_nr - offset ;
		int average = ( a + b + c ) / 3 ;
		if ( test_msg_on ) printf ( "assert ( avg3 ( %d, %d, %d ) == %d ) ;\n" , a , b , c , average ) ;
		//assert ( avg3 ( a, b, c ) == average )
	}
} 

int main (void)
{
 genTest ( 20 , 200 , 100 , 1 ) ;
return EXIT_SUCCESS ;
}
