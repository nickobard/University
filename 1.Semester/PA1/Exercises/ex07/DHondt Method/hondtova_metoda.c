#include <stdio.h>
#include <stdlib.h>

int preference ( int votes, int places )
{
	if ( places == 0 )
	return votes / 1.42 ;
	else 
	return votes / ( 1 + places ) ;
}

int assignMax ( int * votes , int * assigned, int length )
{
	int equalVotes = 0  ;
	int i, lastMax = 0  ;
	int max = votes [0] ;
	for ( i = 1 ; i < length ; i++ )
	{
		if ( preference ( votes [ i ], assigned [ i ] ) > preference ( max, assigned [ lastMax ] ) )
		{
			equalVotes = 0 ;
			max = votes [ i ] ;
			lastMax = i ;
		}
		else if ( preference ( votes [ i ], assigned [ i ] ) == preference ( max, assigned [lastMax] ) && ( assigned [lastMax] == assigned [ i ] ) )
		{
			equalVotes = 1 ;
		} 
	}
	
	if ( equalVotes )
	{
		printf ( "Nelze rozdelit.\n" ) ;
		return EXIT_FAILURE ;
	}
	assigned [lastMax] ++ ;
	return EXIT_SUCCESS ;
}

int main ( void ) 
{
	int n;
	printf ( "Pocet stran:\n" ) ;
	if ( scanf ( "%d" , &n ) != 1 || n < 2 || n > 26 ) 
	{
		printf ( "Nespravny vstup.\n" ) ;
		return 1 ;
	}
	
	int votes [26] = {} ; // from 65 to 90, from A to Z 
	
	printf ( "Strany a pocet hlasu:\n" ) ;
	for ( int i = 1 ; i <= n ; i ++ )
	{
		char party ;
		int number ;
		if ( scanf ( " %1c %d" , &party , &number ) != 2 || party < 65 || party > 64 + n || number <= 0 )
		{
			printf ( "Nespravny vstup.\n" ) ;
			return 1 ;
		}
		
		if ( votes[party - 65] == 0 ) votes[party - 65] = number ;
		else 
		{
			printf ( "Nespravny vstup.\n" ) ;
			return 1 ;		
		}
	
	}
	
	int workers ;
	int assigned [26] = {} ;
	printf ( "Pocet horniku:\n" ) ;
	if ( scanf ( "%d", &workers ) != 1 || workers <= 0 )
	{
		printf ( "Nespravny vstup.\n" ) ;
		return 1 ;
	}
	
	
	
	for ( int i = 0 ; i < workers ; i ++ )
	{
		if ( assignMax ( votes , assigned, n) ) return 1 ;
	}
	
	printf ( "Pridelene pocty:\n" ) ;
	
	for ( int i = 0 ; i < n ; i++ )
	{
	printf ( "%c: %d\n", i + 65 , assigned[ i ] ); 
	}
	
	return 0 ;
}

