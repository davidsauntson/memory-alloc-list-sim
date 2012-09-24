/*
 Memory Allocation List Simulator
 MAL_operation.h 
 
 MAL_operation HEADER FILE
 
 SOPHIE DAVISON
 March 2011
 
 */

#include <string>

using namespace std ;

class MAL_operation		// MAL represents Memory Allocation List
{
public:
	
	MAL_operation() ;
	MAL_operation( string o , int n ) ;
	~MAL_operation() ;

	string operation ;
	int temp_n ;
} ;
