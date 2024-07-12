#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h> //EXIT_SUCCESS = 0; EXIT_FAILURE = 1;
#include <assert.h>
#endif /* __PROGTEST__ */

// 			 30: 8'786'580, 
// 			 31: 9'079'466
//			 28: 8'200'808
//			 29: 8'493'694
//			 
//			 365: 106'903'390
//			 366: 107'196'276
#define CONSUME_PER_DAY 292886LL
#define CONSUME_PER_YEAR 106903390LL
#define IS_LEAP 1
#define NOT_LEAP 0

/*----------------------------------------DAYS------------------------------------------*/

int isLeap ( int year ) 
{
	if ( year % 4000 == 0 ) return NOT_LEAP ;
	if ( year % 400 == 0 ) return IS_LEAP ;
	if ( year % 100 == 0 ) return NOT_LEAP ;
	if ( year % 4 == 0 ) return IS_LEAP ;
	return NOT_LEAP ;
}

int currentDayIndex (int day, int month, int year, int *idx )
{
    if ( year < 1600
    	|| month > 12 
    	|| month < 1 
    	|| day < 1 ) return EXIT_FAILURE ;
    
    
	if ( isLeap ( year ) ) 
		{
			/* calculate day index for LEAP year. */
			int days [] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;
			if ( day > days [ month - 1 ] ) return EXIT_FAILURE ;
			
			*idx = day ;
			for ( int i = 0 ; i < month - 1 ; i++ )
			{
				*idx += days [ i ] ;
			}
			
		}
	else
		{
			/* calculate day index for NOT LEAP year. */
			int days [] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;
			if ( day > days [ month - 1 ] ) return EXIT_FAILURE ;
			
			*idx = day ;
			for ( int i = 0 ; i < month - 1 ; i++ )
			{
				*idx += days [ i ] ;
			}
		}
    return EXIT_SUCCESS ;
}

int leapDays ( int y1, int y2 )
{
	y1 = y1/4 - y1/100 + y1/400 - y1/4000;
	y2 = y2/4 - y2/100 + y2/400 - y2/4000;
	return y2 - y1;
	
}

int deltaDays ( int d1, int d2, int m1, int m2, int y1, int y2, int * delta_d, int * delta_y )
{
	int days_1, days_2 ;
	
	if ( currentDayIndex ( d1, m1, y1, &days_1 ) == EXIT_FAILURE 
	  || currentDayIndex ( d2, m2, y2, &days_2 ) == EXIT_FAILURE ) return EXIT_FAILURE; 
	  
	 *delta_y = y2 - y1;
	 *delta_d += days_2 - days_1 ;
	if ( *delta_d < 0 && *delta_y < 1 ) return EXIT_FAILURE ;
	delta_d += leapDays ( y1 - 1 , y2 - 1 );
	return EXIT_SUCCESS;
}

void swapValues ( int * value_1, int * value_2 )
{
	int tmp = *value_1 ;
	*value_1 = *value_2 ;
	*value_2 = tmp;
}

int deltaTime ( int *h1, int *i1, int *h2, int *i2 , int * delta_t )
{

	int t1 = *h1 * 60 + *i1 ;
	int t2 = *h2 * 60 + *i2 ;

	if ( t2 < t1 ) 
	{
		swapValues ( h1, h2 ) ;
		swapValues ( i1, i2 ) ;
	}
	
	*delta_t = t2 - t1 ;

	return EXIT_SUCCESS ;
}



void absoluteConsum ( int delta_h, int delta_i, int delta_d, int delta_y, long long int * consumption )
{
	
	*consumption += delta_i * 200 + delta_i / 10 * 30;
	*consumption += delta_h * 12200 + delta_h / 10 * 30;
	
	*consumption += delta_d * CONSUME_PER_DAY ;
	*consumption += delta_y * CONSUME_PER_YEAR ;
}

int digitsConsum ( int start, int delta, int arr[], int modulo, int * sum )
{
	int over = 0;
	if ( start + delta >= modulo ) over = 1 ;
	for ( int i = 1 ; i <= delta ; i++  )
	{
		
		*sum += arr[start] ;
		start ++;
		start %= modulo;
	}
	return over;
	
}

int relativeConsum ( int delta_h, int delta_i, int start_h, int start_i )
{		
	int mod10  [] = {4, 5, 2, 3, 3, 1, 5, 4, 1, 2}; // 0-8 + 9 -> 0
	int mod6   [] = {4, 5, 2, 3, 3, 3}; 			// 0-4 + 5 -> 0
	int sum = 0 ;
	
	int i_units = delta_i % 10 ;
	int i_decad = delta_i / 10 ;
	int h_units = delta_h % 10 ;
	int h_decad = delta_h / 10 ;
	
	if ( digitsConsum ( start_i % 10, i_units , mod10, 10, &sum ) ) i_decad += 1;
	if ( digitsConsum ( start_i / 10, i_decad ,  mod6,  6, &sum ) ) h_units += 1;
	if ( digitsConsum ( start_h % 10, h_units , mod10, 10, &sum ) ) h_decad += 1;
		 digitsConsum ( start_h / 10, h_decad , mod10, 10, &sum ) ;
	
	return sum;
	
}

/*--------------------------------MAIN-FUNCTIONS------------------------------------------*/

int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
	if ( h1 > 23 || h2 > 23 || h1 < 0 || h2 < 0 ) return 0 ;
	if ( i1 > 59 || i2 > 59 || i1 < 0 || i2 < 0 ) return 0 ;
	if ( y1 > y2 ) return 0 ;
	
	int delta_t = 0 ;
	
	int delta_d = 0 ;
	int delta_y = 0 ;
	
   	if ( deltaDays ( d1, d2, m1, m2, y1, y2, &delta_d , &delta_y ) == EXIT_FAILURE ) return 0 ;
   	deltaTime ( &h1, &i1, &h2, &i2, &delta_t ) ;
   	if ( delta_t == 0 && delta_d == 0 ) { *consumption = 0 ; return 1 ; }
	if ( delta_t <  0 && delta_d == 0 ) return 0 ;
	
	int delta_i = delta_t % 60;
	int delta_h = delta_t / 60;
	
	*consumption = 0;
	
	absoluteConsum ( delta_h, delta_i, delta_d, delta_y, consumption );
	
	if ( delta_t < 0) *consumption -= relativeConsum ( -delta_h, -delta_i, h1, i1 );
																 
	else 		      *consumption += relativeConsum (  delta_h,  delta_i , h1, i1 );
		 
	 
	printf ( "Consumption is %lld\n" , *consumption );
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;
 
/*--------------------------------OWN-ASSERTS---------------------------------------------*/
    
     assert ( energyConsumption ( 2079, 5, 15, 14, 0,
     							  2154, 4, 27, 3, 50, &consumption ) == 1
           && consumption == 8017630180LL); 
   
    
    assert ( energyConsumption ( 2069, 6, 23, 0, 30,
                                 2069, 6, 23, 10, 15, &consumption ) == 1
           && consumption == 118984LL); 
   
    assert ( energyConsumption ( 2024, 4, 6, 17, 57, 
                                 2024, 4, 6, 19, 51, &consumption ) == 1 ); 
                                 
    assert ( energyConsumption ( 2024, 4, 6, 19, 51, 
                                 2024, 4, 7, 17, 57, &consumption ) == 1 ); 
  
    assert ( energyConsumption ( 2024, 6, 10, 19, 51, 
                            200276698, 4, 7, 17, 57, &consumption ) == 1 
           && consumption == 21424251378018524LL); 
    
    
   assert ( energyConsumption  ( 2023,  1 ,   1, 00, 00,
                                 2023,  3 ,   1, 00, 00, &consumption ) == 1
           && consumption == CONSUME_PER_DAY * 59 );
    assert ( energyConsumption  ( 2022, 3 ,   1, 00, 00,
                                 2022,  3 ,   2, 00, 00, &consumption ) == 1
           && consumption == CONSUME_PER_DAY);
    assert ( energyConsumption  ( 2022, 12 ,   1, 00, 00,
                                 2023,  3 ,   1, 00, 00, &consumption ) == 1
           && consumption == CONSUME_PER_DAY * 90 );
   
   assert ( energyConsumption  ( 2023, 12 ,   1, 00, 00,
                                 2024,  3 ,   1, 00, 00, &consumption ) == 1
           && consumption == CONSUME_PER_DAY * 91 );
   
    assert ( energyConsumption ( 2023, 2,  28, 13, 15,
                                 2024, 3 ,   1, 11, 20, &consumption ) == 1
           && consumption == 107465773LL );

    assert ( energyConsumption ( 2023, 2,  28, 13, 15,
                                 2023, 3 ,   1, 11, 20, &consumption ) == 1
           && consumption == 269497LL ); 

    assert ( energyConsumption ( 2024, 2,  29, 13, 15,
                                 2024, 3 ,   1, 11, 20, &consumption ) == 1
           && consumption == 269497LL ); 
 
   assert ( energyConsumption ( 2026, 12,  31, 13, 15,
                                2027, 1 ,   1, 11, 20, &consumption ) == 1
           && consumption == 269497LL ); 
  assert ( energyConsumption ( 2025, 12,  31, 13, 15,
                               2026, 1 ,   1, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
           // nefunguje pro leap roky
  assert ( energyConsumption ( 2020, 12,  31, 13, 15,
                               2021, 1 ,   1, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  
  assert ( energyConsumption ( 1605,  1 ,1, 16, 24,
  							   1605,  12, 31, 16, 24, &consumption ) == 1 
  							   &&   consumption == 106'610'504LL );
 
  assert ( energyConsumption ( 1604,  1 ,1, 16, 24,
  							   1604,  12, 31, 16, 24, &consumption ) == 1 
  							   &&   consumption == 106'903'390LL );
  
  assert ( energyConsumption ( 1604,  2 ,29, 16, 24,
  							   4004,  2, 29, 16, 24, &consumption ) == 1 
  							   &&  ( consumption > 0 ) );
  
  assert ( energyConsumption ( 1604,  2 ,29, 16, 24,
  							   4004,  2, 29, 16, 24, &consumption ) == 1 
  							   &&  ( consumption > 0 ) );
  assert ( energyConsumption ( 1600,  2 ,28, 16, 24,
  							   4000,  2, 28, 16, 24, &consumption ) == 1 
  							   &&  ( consumption > 0 ) );
  
  assert ( energyConsumption ( 2004,  2 ,29, 16, 24,
  							   2004,  3,  1, 16, 24, &consumption ) == 1 
  							   && consumption == 292886LL );
  
  assert ( energyConsumption ( 2005,  2 ,28, 16, 24,
  							   2005,  3, 1, 16, 24, &consumption ) == 1 
  							   && consumption == 292886LL );
  
  assert ( energyConsumption ( 2004, 12,31, 16, 24,
  							   2005,  1, 1, 16, 24, &consumption ) == 1 
  							   && consumption == 292886LL );
  assert ( energyConsumption ( 2003, 12,31, 16, 24,
  							   2004,  1, 1, 16, 24, &consumption ) == 1 
  							   && consumption == 292886LL );
  assert ( energyConsumption ( 2000, 12,31, 16, 24,
  							   2001,  1, 1, 16, 24, &consumption ) == 1 
  							   && consumption == 292886LL );
  assert ( energyConsumption ( 1598, 10, 8, 16, 24,
  							   1599, 10, 8, 16, 24, &consumption ) == 0 );
  assert ( energyConsumption ( 1599, 10, 8, 16, 24,
  							   1600, 10, 8, 16, 24, &consumption ) == 0 );
  assert ( energyConsumption ( 1600, 10, 8, 16, 24,
  							   1600, 10, 8, 16, 24, &consumption ) == 1 
 			&& consumption == 0LL );
  assert ( energyConsumption ( 99999999, 10, 8, 16, 24,
  							   99999999, 10, 8, 16, 24, &consumption ) == 1
  			&& consumption == 0LL );
  assert ( energyConsumption ( 19901111, 10, 8, 16, 24,
  							   19901111, 10, 8, 16, 24, &consumption ) == 1 
  	  		&& consumption == 0LL );
 
  assert ( energyConsumption (1990, 4, 9, 16, 58,
  							   1939, 10, 8, 16, 24, &consumption ) == 0 );
  							   
  assert ( energyConsumption ( 1990, 4, 9, 16, 58,
  							   1939, 10, 8, 16, 24, &consumption ) == 0 );
  							   
  assert ( energyConsumption ( 2021, 1, 1, 00, 00,
                               2021, 2, 1, 4134234, 312312, &consumption ) == 0 );  
                               
  assert ( energyConsumption ( -2,  12,  -12, -2, -123,
                               -32,  12,  -1, -12, -1, &consumption ) == 0 ); 
                               
  assert ( energyConsumption ( 2021,  12,  30, 00, 00,
                               20212, 12,  30, 23, 59, &consumption ) == 1 );
 
  assert ( energyConsumption ( 2021,  12,  30, 00, 00,
                               2021, 12,  30, 23, 59, &consumption ) == 1 );
   
  assert ( energyConsumption ( 2021, 01, 01, 23, 59,
                               2021, 01, 01, 23, 59, &consumption ) == 1 
            && consumption == 0LL ); 
  assert ( energyConsumption ( 2021, 00, 00, 00, 00,
                               2021, 00, 00, 00, 00, &consumption ) == 0 ); 
  assert ( energyConsumption ( 2021, 13,  1, 00, 22,
                               2005,  2, 29, 00, 22, &consumption ) == 0 ); 
  assert ( energyConsumption ( 2021, 13,  1, 00, 22,
                               2021, 10,  1, 00, 22, &consumption ) == 0 ); 
 
  assert ( energyConsumption ( 2021, 10,  1, 00, 22,
                               2021, 10,  1, 00, 22, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 00, 12,
                               2021, 10,  1, 00, 11, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10,  1, 00, 15,
                               2021, 10,  1, 00, 22, &consumption ) == 1
           && consumption == 1427LL );
           
  assert ( energyConsumption ( 2021, 10,  1, 00, 15,
                               2021, 10,  1, 00, 32, &consumption ) == 1
           && consumption == 3459LL );
           
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 13, 45, &consumption ) == 1
           && consumption == 6100LL );
           
  assert ( energyConsumption ( 2021, 10,  1, 13, 45,
                               2021, 10,  2, 13, 15, &consumption ) == 1
           && consumption == 286786LL );
           
  assert ( energyConsumption ( 2021, 10,  1, 11, 20,
                               2021, 10,  1, 13, 15, &consumption ) == 1
           && consumption == 23389LL );   
         
           
/*--------------------------------MAIN-ASSERTS--------------------------------------------*/
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  //problem          
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
           
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
           
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
  assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  return 0;
}
#endif /* __PROGTEST__ */
