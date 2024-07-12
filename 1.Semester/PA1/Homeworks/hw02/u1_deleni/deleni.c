#include <stdio.h>
#include <assert.h>
#include <math.h>

/**
 * Function for easier debugging
 * parameter str , put a "string to display"
 * parameter x , put an int to display its current value.
 */
void dbg_int ( const char* str , int x ) ;

/**
 * Function returns number of digits of the integer argument.
 */
int numDigits ( int number ) ;
/**
 * Function which returns i-ths digit of the given number.
 * Use numDigist function and pow functionf of math.h.
 */
int pickDigit ( int number , int digit ) ;

int main ( void ) 
{

	#ifndef __PROGTEST__
	assert ( pickDigit ( 123 , 1 ) == 1 ) ;
	assert ( pickDigit ( 123 , 2 ) == 2 ) ;
	assert ( pickDigit ( 123 , 3 ) == 3 ) ;
	assert ( pickDigit ( 5346 , 1 ) == 5 ) ;
	assert ( pickDigit ( 5346 , 2 ) == 3 ) ;
	assert ( pickDigit ( 5346 , 3 ) == 4 ) ;
	assert ( pickDigit ( 5346 , 4 ) == 6 ) ;
	assert ( pickDigit ( 100 , 2 ) == 0 ) ;
	#endif

	int delen , delit , res ;
	;
	printf ( "Zadejte dve cisla:\n" ) ;
	if ( scanf ( "%d %d" , &delen , &delit ) != 2
			|| delen < 0
			|| delit <= 0 )
	{
		printf ( "Nespravny vstup.\n" ) ;
		return 1 ;
	}
	res = delen / delit ;
	printf ( " %d : %d = %d\n" , delen , delit , res ) ;
	

	int dig_res = numDigits ( res ) ;
	int dig_delen = numDigits ( delen ) ;
	
	int offset = dig_delen - dig_res + 2 ;
	
	for ( int i = 1 ; i <= dig_res ; i++ )
	{
		int meta_delit = -delit * pickDigit ( res , i ) ;
		printf ( "%*d\n" , offset++ , meta_delit ) ;
		
		delen +=  meta_delit * pow ( 10 , dig_res - i ) ;
		if ( i != dig_res )
		{
		printf ( "%*d\n" , offset , ( int ) ( delen / pow ( 10 , dig_res - i - 1 ) ) ) ;
		}
		else
		{
		printf ( "%*d zbytek\n" , --offset , ( int ) ( delen / pow ( 10 , dig_res - i ) ) ) ;
		}
		
	}
	
	return 0 ;
}







int pickDigit ( int number , int digit )
{
	int digits_num = numDigits ( number ) ;
	if ( digit > digits_num || digit < 1 )
	{
		printf ( "%d-nth digit of number %d does not exist.\n" , digit , number ) ;
		return 1 ;
	}
	number /= pow ( 10 , digits_num - digit ) ;
	return number % 10 ;
}

int numDigits ( int number )
{
	int digits = 0 ;
	if ( number == 0 ) return 1 ;
	while ( number > 0 )
	{
		number /= 10 ; 
		digits++ ;
	}
	
	return digits ;
}

void dbg_int ( const char* str , int x )
{
	printf ( "Value of: %s: %d\n" , str , x ) ;
}
