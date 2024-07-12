#include <stdio.h>
#include <stdlib.h>

#define USERS_MAX 100'000
#define LOG_LIMIT 1'000'000
#define QUEST_NR 10
int main ( void ) 
{

/*-----------------------------------EASY-INPUTS---------------------------------------*/
if ( 0 ) 
{
	for ( int i = 0 ; i < LOG_LIMIT ; i ++ )
	{
		printf ( "+ %d\n", i % USERS_MAX ) ;
	}
}
/*-----------------------------------HARD-INPUTS---------------------------------------*/
if ( 1 ) 
{
	for ( int i = 0 ; i < LOG_LIMIT ; i ++ )
	{
		int num = rand () % USERS_MAX ;
		printf ( "+ %d\n", num ) ;
	}
}

	return 0 ;
}
