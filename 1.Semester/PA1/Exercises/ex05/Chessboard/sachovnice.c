#include <stdio.h>
#include <string.h>
 
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
 * Function for getting input for numbers of fields and size of fields
 * input parameters are pointers to output the given data back to main variables 
 * parameter err is for returning error case and stopping main function.
 */
void giveInput ( int *num , int *size , int *err )
{
	printf ( "Zadejte pocet poli:\n" ) ;
	if ( scanf ( "%d" , num ) != 1
		|| *num <= 0 )
	{
		printf ( "Nespravny vstup.\n" ) ;
		*err = 1 ;
	}
	else 
	{
		printf ( "Zadejte velikost pole:\n" ) ;
		if ( scanf ( "%d" , size ) != 1
			|| *size <= 0 )
		{
			printf ( "Nespravny vstup.\n" ) ;
			*err = 1 ;
		}
	}
}

/**
 * Print chess desk using input parameters number of fields
 * and size of each field. 
 * Print border edge of the chess desk.
 */
int main ( void ) 
{

int number , size ;
int err = 0 ;

giveInput ( &number , &size , &err) ;
if ( err ) return 1 ;

/* Declare variable total_s to count total width of the desk from 0 to total_s + \n
 * Declare type_v variable for determining later if the field is empty or filled with X-es.
 */

int total_s = number * size + 1 ;
int type_v = 0 ;
/* First for cycle goes through each line,
 * printing it with needed characters.
 */
for ( int i = 0 ; i <= total_s ; i++ )
	{
		/* Declare type_h in the loop body, because it is neccessary
		 * to reset its value to 0 for each line.
		 */
		int type_h = 0 ;
		
		/* The first or the last ( total_s ) line are border edges,
		 * if it is border edge, print border symbol.
		 * else (if it is not top or bottom edge), fill it with chess desk symbols
		 * and first side and last side symbols ('|').
		 */
		if ( i == 0 || i == total_s )
			{
				/* Print symbol for each position.
				 * If its the first or the last (=total_s) position, print '+'
				 */
				for ( int i = 0 ; i <= total_s ; i++ )
				{
					if ( i == 0 ) printf ( "+" ) ;
					else if ( i == total_s ) printf ( "+\n" ) ;
					else printf ( "-" ) ;
				}
			}
		else 
			{
				/* Cycle for each symbol position in the line, from 0 (left border),
				 * to total_s (right border).
				 * Between is ' ' or 'X', depends on type_h and type_w variables.
				 */
				for ( int i = 0 ; i <= total_s ; i++ )
				{
					 
					
					if ( i == 0 ) printf ( "|" ) ;
					else if ( i == total_s ) printf ( "|\n" ) ;
					
					else
					{
						/* type_h or type_v decides, it its empty or not.
						 * e.g. size = 3 ;
						 * type_h = size * 2 -> 3 * 2 -> 6 ;
						 * if 6 > size , 6 < 3 -> empty (' ' symbol)
						 * then 6-- = 5 -> empty
						 * ....
						 * 4-- = 3
						 * if 3 > 3 is false, -> else print 'X'
						 * When type_h is 0 -> type_h = size * 3 = 6,
						 * the cycle repeats, we have 3 ' ' and 3 'X'
						 */
						if ( type_v == 0 ) type_v = size * 2 ;
						
						if ( type_v > size )
							{
								if ( type_h == 0 ) type_h = size * 2 ;
								if ( type_h > size ) printf ( " " ) ;
								else printf ( "X" ) ;
								//dbg_int("type",type);
								type_h-- ;
							}	
							/* If our line starst with X-es,
							 * just exchange ' ' for 'X' in printf function,
							 * the cycle of type_w and type_h is the same.
							 */
						else 
							{
								if ( type_h == 0 ) type_h = size * 2 ;
									if ( type_h > size ) printf ( "X" ) ;
									else printf ( " " ) ;
									//dbg_int("type",type);
									type_h-- ;
							}
					}
				}
					/* For every line change type_v variable value.
					 */
				type_v-- ;
			}
	}




//dbg_int ( "number of fields" , number ) ;
return 0 ;
}
