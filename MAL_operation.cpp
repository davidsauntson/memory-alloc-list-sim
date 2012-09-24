/*
 Memory Allocation List Simulator
 MAL_operation.cpp 
 
 MAL_operation IMPLEMENTATION FILE
 
 SOPHIE DAVISON
 March 2011
 
 */


#include "MAL_operation.h"
#include <string> 

MAL_operation :: MAL_operation( string o , int n )
  : operation( o ) , temp_n( n ) { }               


MAL_operation :: MAL_operation() { }

MAL_operation :: ~MAL_operation() { }
