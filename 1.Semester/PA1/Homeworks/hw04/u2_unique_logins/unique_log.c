#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERS_MAX 100'000
#define LOG_LIMIT 1'000'000
#define UNUSED -1

int scanUser ( int * user_id, int * users ) ;

int scanInterval ( int * last_entry, int * from, int * len ) ;

void findUniques ( int * target_arr, const int * source_arr, int len ) ;

int cmp ( const void *a, const void *b ) ;

 /**
  * Program to detect entries of users under individual ID.
  * + operator to entry user, ? operator to specify a range from-to of elements
  * to find unique entries.
  * entry format is:	+ id_number
  * question format is:	? from_number to_number
  * all inputs are integers
  */
int main ( void )
{
	int user_id    = 0 ;
	int last_entry = 0 ;
	
	int users_logs [ USERS_MAX ] = {} ;
	int log_history [ LOG_LIMIT ] = {} ;
	int * sort_buffer = ( int * ) malloc ( sizeof ( *sort_buffer ) * LOG_LIMIT ) ;
	
	char input_sign ;
	int from, len ;
	int err ;
	
	
	printf ( "Pozadavky:\n" ) ;
	
	/*
	 * Read operator from standard input.
	 * - if + operator -> scanUser function.
	 * - if ? operator -> scanInterval and findUniques functions
	 * - if error -> break loop and check whether EOF or return EXIT_FAILURE.
	 */
	while ( ( err = scanf ( " %c" , &input_sign ) ) == 1 )
	{
	
		if ( input_sign == '+' && last_entry < LOG_LIMIT )
		{
			if ( scanUser ( &user_id, users_logs ) ) break;
			log_history [ last_entry ++ ] = user_id ;
		}
		else if ( input_sign == '?' )
		{
			if ( scanInterval ( &last_entry, &from, &len ) ) break;
			findUniques ( sort_buffer + from, log_history + from, len ) ;
		}
		else 
			break;
	}
	
	if ( err != EOF || last_entry == 0 )
	{
		printf ( "Nespravny vstup.\n" ) ;
		free ( sort_buffer ) ;
		return EXIT_FAILURE ;
	}
	
	free ( sort_buffer ) ;
	return EXIT_SUCCESS ;
}

 /**
  * Scan each user id and saves it in history and saves a number of entries
  *
  * Read from standard input in interval < 0, 99999 >
  * Each entry store in user_logs array, each user id is the number of the element
  * in the user_logs array, where is stored number of entries, incremented after each entry.
  *
  * Then if that was first entry ( 0 entries before ), print "> prvni navsteva"
  * Otherwise, print the number of current entries under specified user id.
  *
  * @param[in] uid		- user id
  * @param[out] users_logs		- array to store individual number of enries
  */

int scanUser ( int * uid, int * users_logs ) 
{
	 /*
	  * Input + 1.56, where is the double instead of integer will print message about entry
	  * using integer value, ignoring .56, but only after will detect error.
	  * This was solved in previos commits, but neglected now to make function work faster
	  * and do not check, whether something is after the integer.
	  */
	if ( scanf ( " %d" , uid ) != 1 
		|| *uid < 0 
		|| *uid >= USERS_MAX ) return EXIT_FAILURE ;

	if ( users_logs [*uid] ++ == 0 ) 
		printf ( "> prvni navsteva\n" ) ;
	
	else 
		printf ( "> navsteva #%d\n" , users_logs [*uid] ) ;
	
	return EXIT_SUCCESS ;
}

 /**
  * Scan interval from - to and calculate the length of the given interval.
  *
  * Read from standard input, then check if interval is correct and do not exceed current
  * last entry in history.
  *
  * @param[in] last_entry 		- last entry in history
  * @param[out] from	- where desired interval begins
  * @param[out] len 	- length of the interval 
  */
int scanInterval ( int * last_entry, int * from, int * len )
{
	int to ;
	
	if ( scanf ( " %d %d" , from , &to ) != 2 
		|| *from < 0 
		|| *from > to 
		|| to >= *last_entry ) return EXIT_FAILURE ;
		
	*len = to - *from + 1 ;
	
	return EXIT_SUCCESS ;
}

 /**
  * Get two array pointers uisng which do copying and sorting for specified interval length.
  * After sorting count how many unique numbers is in the interval and print it with the length.
  *
  * @param[in] source_arr  - pointer to elements in log history array,
  * from where to copy to other buffer array. 
  * It is important to use another array and do not change history!
  *
  * @param[in] target_arr	- pointer to element in allocated array,
  * from where to copy the current interval of history for further sorting.
  *
  * After copying and sorting target interval for specified length ( len parameter )
  * find and count unique numbers. Go through each element, every time when encounter
  * new element, increment unique number counter.
  
  * @local last	- variable to remember last elements and compare if next elements is
  * the same or not. If not -> update last to current different element and proceed.
  */
void findUniques ( int * target_arr, const int * source_arr, int len )
{
	memcpy ( target_arr , source_arr , sizeof ( *target_arr ) * len ) ;
	qsort  ( target_arr , len, sizeof ( *target_arr ), cmp ) ;
	
	int unique_users = 0 ;
	int last = UNUSED ;
	
	for ( int i = 0; i < len ; i ++ )
	{
		if ( target_arr [ i ] != last )
		{
			last = target_arr [ i ] ;
			unique_users ++ ;
		}
	}
	
	printf ( "> %d / %d\n", unique_users, len ) ;
}
 /**
  * Formal function for qsort function in findUniques elements.
  * Is used to compare two integers in the sorted array.
  *
  * if eqal elements - 0
  * otherwise 1 or -1 if greater or lesser.
  */
int cmp ( const void *a, const void *b )
{
	int nm1 = *(const int * ) a ;
	int nm2 = *(const int * ) b ;
	
	if ( nm1 > nm2 ) return  1 ;
 	if ( nm1 < nm2 ) return -1 ;
 	return 0 ;
	
}









