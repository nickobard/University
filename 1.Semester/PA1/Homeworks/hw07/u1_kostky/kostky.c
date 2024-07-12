#include <stdio.h>
#include <stdlib.h>


int g_count ;

int cmp ( const void *a, const void *b )
{
	int nm1 = *(const int * ) a ;
	int nm2 = *(const int * ) b ;
	
	if ( nm1 > nm2 ) return -1 ;
 	if ( nm1 < nm2 ) return  1 ;
 	return 0 ;
	
}

void print ( int * arrPrint, int len )
{
	g_count ++ ;
	for ( int i = 0 ; i < len ; i ++ )
	{
		printf ( "%d, " , arrPrint [ i ] ) ;
	}
	printf ( "%d\n" , arrPrint [ len] ) ; 
}

void buildTower ( int p_len, int * pieces, int * buffer, int b_len )
{

	
	for ( int i = 0; i < p_len ; i++ )
	{
		
		buffer [ b_len ] = pieces [i] ;
		
		if ( p_len != 1 )
		{
			buildTower ( p_len - i - 1, pieces + i + 1, buffer, b_len + 1 )	;
		}
		
		print ( buffer , b_len ) ;
		
		while ( pieces [ i + 1 ] == pieces [ i ] ) i ++ ;
	}
}

int main ( void ) 
{
	int len ;
	int * pieces = NULL ; 
	
	printf ( "Pocet kostek:\n" ) ;
	
	if ( scanf ( " %d", &len ) != 1 || len <= 0 )
	{
		printf ( "Nespravny vstup.\n" ) ;
		return EXIT_FAILURE ;
	}
	
	pieces = ( int * ) malloc ( sizeof ( * pieces ) * len ) ;
	
	printf ( "Velikosti:\n" ) ;
	
	for ( int i = 0 ; i < len ; i++ )
	{
		if ( scanf ( " %d", & pieces [ i ] ) != 1 || pieces [ i ] <= 0 ) 
		{
				printf ( "Nespravny vstup.\n" ) ;
				return EXIT_FAILURE ;
		}
	}
	
	qsort  ( pieces , len , sizeof ( *pieces), cmp ) ;

	int * buffer = ( int * ) malloc ( sizeof ( * buffer ) * len ) ;
	
	buildTower ( len, pieces, buffer, 0 );
	
	printf ( "Celkem: %d\n" , g_count ) ;
	
	free ( buffer ) ;
	free ( pieces ) ;
	return EXIT_SUCCESS ;
}
