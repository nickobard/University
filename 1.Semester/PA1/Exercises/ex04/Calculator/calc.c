#include <stdio.h>
#include <math.h>

int main ( void )
{

char equals = '=' ;
char operation = '0';
double a = 0 ;
double b = 0 ;
double result = 0 ;

printf ( "Zadejte vzorec:\n" ) ;

if ( scanf ( " %lf %1c %lf %1c" , &a , &operation , &b , &equals ) != 4 || equals != '=' )
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
result = ( a / b ) ;
printf ( "%g\n" , trunc ( result ) ) ;
return 0 ;

default:
printf ( "Nespravny vstup.\n" ) ;
return 1 ;
}

printf ( "%g\n" , result ) ;

return 0 ;
}
