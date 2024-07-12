#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/*-----------------------------------------------------------*/

	/**
	 * Decide if the number is even or not.
	 */
int isEven ( int num ) 
{
	if ( num % 2 == 0 ) return 1 ;
	return 0 ;
}
/*-----------------------------------------------------------*/

/* Decide if the year is LEAP (1) or NOT LEAP (0) */
int isLeap ( int year ) 
{
	if ( year % 4000 == 0 ) return 0 ;
	if ( year % 400 == 0 ) return 1 ;
	if ( year % 100 == 0 ) return 0 ;
	if ( year % 4 == 0 ) return 1 ;
	return 0 ;
}
/*-----------------------------------------------------------*/

/**
 * Decide how many days there is in the month of the current year.
 * returns number of days.
 */
int monthDays ( int month , int isLeap )
{
	if ( month == 2 && isLeap ) return 29 ;
	else if ( month == 2 && !isLeap ) return 28 ;
	
	if ( month < 8 )
	{
		if ( isEven ( month ) ) return 30 ;
		else return 31 ;
	}
	else 
	{
		if ( isEven ( month ) ) return 31 ;
		else return 30 ;
	}
	
	return 0 ;
}
/*-----------------------------------------------------------*/

	/**
	 *	Calculate the number of days to idx pointer.
	 *
	 */
void calcDays ( int day , int month , int isLeap , int *out )
{
	*out = day ;
			
			for ( int i = 1 ; i < month ; i++ )
			{
				*out += monthDays ( i , isLeap ) ;
			}
}
/*-----------------------------------------------------------*/

	/**
	 * Decide right parameters and calc resulting number of days
	 * for every situation.
	 * 
	 */
int dateToIndex(int day, int month, int year, int *idx) {
    /* TODO: Your code here */ 
    /**
     * Make sure the inptu is correct,
     */
    if ( year < 2000 
    	|| month > 12 
    	|| month < 1 
    	|| day < 1 ) return 0 ;
    
	if ( isLeap ( year ) ) 
		{
			/* calculate day index for LEAP year. */
			if ( day > monthDays ( month , 1 ) ) return 0 ;
			calcDays ( day , month , 1 , idx ) ;
		}
	else
		{
			/* calculate day index for NOT LEAP year. */
			if ( day > monthDays ( month , 0 ) ) return 0 ;
			calcDays ( day , month , 0 , idx ) ;
		}
		
    return 1 ;
}
/*-----------------------------------------------------------*/

#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
/*-----------------------------------------------------------*/
    assert (isEven(2) == 1) ;
    assert (isEven(3) == 0) ;
	assert (isEven(100) == 1) ;
	assert (isEven(30) == 1);
	assert (isEven(27) == 0);
/*-----------------------------------------------------------*/
	assert (isLeap(4404) == 1);
    assert (isLeap(4108) == 1);
    assert (isLeap(2400) == 1);
    assert (isLeap(2403) == 0);
    assert (isLeap(4233) == 0);
    assert (isLeap(2123) == 0);
    assert (isLeap(2023) == 0);
    assert (isLeap(2010) == 0);
/*-----------------------------------------------------------*/    
    assert (monthDays(1,1) == 31 );
    assert (monthDays(2,1) == 29 );
    assert (monthDays(3,1) == 31 );
    assert (monthDays(4,1) == 30 );
    assert (monthDays(5,1) == 31 );
    assert (monthDays(6,1) == 30 );
    assert (monthDays(7,0) == 31 );
    assert (monthDays(8,0) == 31 );
    assert (monthDays(9,0) == 30 );
    assert (monthDays(10,0) == 31 );
    assert (monthDays(11,0) == 30 );
    assert (monthDays(12,0) == 31 );
    assert (monthDays(2,0) == 28 );
/*-----------------------------------------------------------*/
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);    
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    return 0;
}
#endif /* __PROGTEST__ */

