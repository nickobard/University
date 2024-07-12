#include <stdio.h>
#include <math.h>
#include <float.h>

int equalDoubles ( double a , double b )
{
if ( ( abs ( a - b ) <= DBL_EPSILON * abs ( a + b ) ) )
{
return 1 ;
}

return 0 ;
}

int main ( void )
{

char operation = '0';
double a = 0 ;
double b = 0 ;
double c = 0 ;
double result = 0 ;

printf ( "Zadejte rovnici:\n" ) ;

if ( scanf ( " %lf %1c %lf = %lf" , &a , &operation , &b , &c ) != 4 )
{
printf ( "Nespravny vstup.\n" ) ;
return 1 ;
} 

switch ( operation ) 
{
case '+' :
result = a + b ;

break ;

case '-' :
result = a - b ;
break ;

case '*' :
result = a * b ;
break ;

case '/' :
if ( b == 0 )
{
printf ( "Nespravny vstup.\n" ) ;
return 1 ;
}
result = trunc ( ( a / b ) ) ;
break ;

default:
printf ( "Nespravny vstup.\n" ) ;
return 1 ;
}

if ( equalDoubles ( result , c ) )
{
printf ( "Rovnice je spravne.\n" ) ;
return 0 ;
}
else
{
printf ( "%g != %g\n" , result , c ) ;
#ifndef __PROGTEST__
//printf ( "%.1000lf != %.1000lf\n" , result , c ) ;
#endif 
return 1 ;
}

return 0 ;
}
