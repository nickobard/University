#include <stdio.h>
#include <math.h>
#include <float.h>

int NotEqualDoubles ( double a , double b )
{
	if ( fabs ( a - b ) <= 1e-6 * fabs ( a + b ) )
	{
	return 0 ;
	}
	return 1 ;
}


void caseErr ( void )
{
	printf ( "Nespravny vstup.\n" ) ;
} 

int askOverlap ( double *over ) 
{
printf ( "Prekryv:\n" ) ;
			
		if ( scanf ( "%lf" , over ) != 1
			|| *over < 0 )
		{
			caseErr () ;
			return 1 ;
		}
		return 0 ;
}

int calcOrientation ( double f_size , double s_size , double *over )
{

	double sum = f_size ;
	int pieces = 1 ;

	while ( sum < s_size && NotEqualDoubles ( sum , s_size ) )
	{
	
	if ( *over < 0 ) {
		
		if ( askOverlap ( over ) == 1 )
		{
			return -1 ;
		}
	}

	if ( f_size <= *over )
	{
	return 0 ;
	}

	sum += f_size - *over ;
	pieces ++ ;
	}
	
	return pieces ;
}



int main ( void ) 
{

	/* Input fibre size, make sure, that it is not 0 or negative */
	printf ( "Velikost latky:\n" ) ;

	double fibre_w ;
	double fibre_h ;
	
	if ( scanf ( "%lf %lf" , &fibre_w , &fibre_h ) != 2
		|| fibre_w <= 0
		|| fibre_h <= 0 )
	{
	caseErr () ;
	return 1 ;
	}

	/* Input sail size, make sure, that it is not 0 or negative */
	printf ( "Velikost plachty:\n" ) ;

	double sail_w ;
	double sail_h ;

	if ( scanf ( "%lf %lf" , &sail_w , &sail_h ) != 2
		|| sail_w <= 0
		|| sail_h <= 0 ) 
	{
	caseErr () ;
	return 1 ;
	}
	
	double overlap = -1 ;
	double *ptr = &overlap ;
		
	int totalPieces = 0 ;
	int orient_1 = 0 ;
	int orient_2 = 0 ;
	
	if ( fibre_w == fibre_h )
	{
		orient_1 = calcOrientation ( fibre_w , sail_w , ptr ) ;
		if ( orient_1 != -1 )
		orient_1 *= calcOrientation ( fibre_h , sail_h , ptr ) ;
		else
		{
		return 1 ;
		}
	}
	else if ( fibre_w == sail_h && fibre_h == sail_w )
	{
		orient_1 = 1 ;
	}
	else
	{
	
		orient_1 = calcOrientation ( fibre_w , sail_w , ptr ) ;
		if ( orient_1 != -1 )
		orient_1 *= calcOrientation ( fibre_h , sail_h , ptr ) ;
		else
		{
		return 1 ;
		}
		if ( orient_1 != 1 ) {
		if ( orient_1 != -1 )
		orient_2 = calcOrientation ( fibre_h , sail_w , ptr ) ;
		else
		{
		return 1 ;
		}
		if ( orient_1 != -1 )
		orient_2 *= calcOrientation ( fibre_w , sail_h , ptr ) ;
		else 
		{
		return 1 ;
		}
		}
	}
	
	if ( orient_1 == 0 && orient_2 == 0 )
	{
	printf ( "Nelze vyrobit.\n" ) ;
	return 1 ;
	}
	else if ( orient_1 == 0 )
	{
	totalPieces = orient_2 ;
	}
	else if ( orient_2 == 0 )
	{
	totalPieces = orient_1 ;
	}
	else
	{
	totalPieces = orient_1 < orient_2 ? orient_1 : orient_2 ;
	}
	
	//printf ( "Overlap in main is: %lf\n" , overlap ) ;
	printf ( "Pocet kusu latky: %d\n" , totalPieces ) ;
	
	return 0 ;
}















