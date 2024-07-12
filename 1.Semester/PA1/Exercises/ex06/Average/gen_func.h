long long avg3 ( long long a, long long b, long long c );

void genTest ( int tests_nr , int size_nr , int offset , int test_msg_on , int time_rand, int seed = 0 ) 
{
	if ( time_rand == 0 ) srand ( seed ) ;
	else srand ( time ( NULL) ) ;
	
	
	for ( int i = 0 ; i < tests_nr ; i ++ )
	{	
		int a = rand () % size_nr - offset ;
		int b = rand () % size_nr - offset ;
		int c = rand () % size_nr - offset ;
		int average = ( a + b + c ) / 3 ;
		
		if ( test_msg_on ) printf ( "assert ( avg3 ( %d, %d, %d ) == %d ) ;\n" , a , b , c , average ) ;
		
		assert ( avg3 ( a, b, c ) == average ) ;
	}
	
	printf ( "\nAll random tests succeeded!\n\n" ) ;
	
} 

/**
 * --------------------------ANOTHER-VARIANT-OF-GENERATOR---------------------------- *
 *
 
 for (int i = 0; i < n; i++)
    {
        // Note: This method of generating random numbers in a range isn't suitable for
        // applications that require high quality random numbers.
        // rand() has a small output range [0,32767], making it unsuitable for
        // generating random numbers across a large range using the method below.
        // The approach below also may result in a non-uniform distribution.
        // More robust random number functionality is available in the C++ <random> header.
        // See https://docs.microsoft.com/cpp/standard-library/random
        
->      int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
->      printf("  %6d\n", r);
    

*/

