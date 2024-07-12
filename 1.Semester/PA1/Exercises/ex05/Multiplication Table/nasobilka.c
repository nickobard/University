#include <stdio.h>
#include <assert.h>

/**
 * Function for easier debugging
 * parameter str , put a "string to display"
 * parameter x , put an int to display its current value.
 */
void dbg_int ( const char* str , int x )
{
printf ( "Value of: %s: %d\n" , str , x ) ;
}

/**
 * Function returns number of digits of the integer argument.
 */
int numDigits ( int number )
{
	int digits = 0 ;
	while ( number > 0 )
	{
		number /= 10 ; 
		digits++ ;
	}
	return digits ;
}

/**
 * Program creates multiply table without repeating (triangle form).
 * Rows/columns 1 for numbers range, 2 for border,
 * from 3 to n (max value of range) for myltiplies.
 */
int main ( void ) 
{
	#ifndef __PROGTEST__
	assert ( numDigits ( 100 ) == 3 ) ;
	assert ( numDigits ( 2455 ) == 4 ) ;
	assert ( numDigits ( 1 ) == 1 ) ;
	#endif
	
	int n ;

	printf ( "Rozsah:\n" ) ;
	if ( scanf ( "%d" , &n ) != 1
		|| n < 1 ) 
	{
		printf ( "Nespravny vstup.\n" ) ;
		return 1 ;
	}
	
	int max_space , n_space ;
	
	max_space = numDigits ( n * n ) + 1 ;
	n_space = max_space - 1 ;

	int rows_num = 1 ;	
	
	/* Algorithm which prints the table.
	 * It differs 3 cases - line/column 1, 2, and others
	 * for 1 - print the range line and range column
	 * for 2 - print the border edge using symbols '+','-' and '|'
	 * for the rest - multiply current row number with current column number
	 * do not repeat same multiplies if column num == row num - 1
	 * e.g. column 2 == 2 - 1 -> 2 == 1 (which multiply already was on row num = 1 before)
	 */
	for ( int i = 1 ; i <= n + 2 ; i++ )
	{
		int tables_num = n ;
		if ( i == 1 )
		{
			printf ( "%*c" , n_space + 1 , '|' ) ;
			for ( int i = 1 ; i <= n ; i++ ) 
			{
				printf ( "%*d" , max_space , tables_num-- ) ;
			}
		}
		else if ( i == 2 )
		{
			for ( int i = 1 ; i <= 3 ; i++ )
			{   
				if ( i == 1 )
				{
					for ( int l = 1 ; l <= n_space ; l++ )
					{
						printf ( "-" ) ;
					}
				}
				else if ( i == 2 ) printf ( "+" ) ;
				else 
				{
					for ( int l = 1 ; l <= max_space * n ; l++ )
					{
					printf ( "-" ) ;
					}
				}
			}
		}
		else
		{
			for ( int i = 1 ; i <= n + 2 ; i++ )
			{
				if ( i == 1 )
				{
					printf ( "%*d" , n_space , rows_num ) ;
				}
				else if ( i == 2 ) printf ( "|" ) ;
				else
				{
				if ( tables_num == rows_num - 1 )
				{
					break ;
				}
					printf ( "%*d" , max_space , rows_num * tables_num ) ;
					tables_num-- ;
				}
				
			}
			rows_num++ ;
		}
		
		printf ( "\n" ) ;
	}
	return 0 ;
}
