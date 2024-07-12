#include <stdio.h>
#include <stdlib.h>

#define TESTS_NR 20
#define DIVISOR 200
#define RANGE 100
int main ( void ) 
{
	for ( int i = 0 ; i < TESTS_NR ; i++ )
	{
		int a = rand () % DIVISOR - RANGE ;
		int b = rand () % DIVISOR - RANGE ;
		int c = rand () % DIVISOR - RANGE ;
		
		printf ( "assert ( avg3 ( %d, %d, %d ) == %d ) ;\n" , a , b , c , (a + b + c)/3 ) ;
	}
	
	return EXIT_SUCCESS ;
}
