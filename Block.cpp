
/*
 Memory Allocation List Simulator
 Block.cpp
 
 Block IMPLEMENTATION FILE
 
 DAVID SAUNTSON 
 March 2011
 
 */


#include <iostream>
#include "Block.h"
#include "definitions.h"

using std :: ostream ;

//CONSTRUCTOR & DESTRUCTOR

Block :: Block()
{
	next_block = NULL ;
	prev_block = NULL ;
}

Block :: Block( bool f , int s , int bID ) 
    : free( f ) , size( s ) , blockID( bID ) { }


//ACCESSORS

bool Block :: isFree()		{ return free ; }

int Block :: getSize()		{ return size ; }

int Block :: getBlockID()	{ return blockID ; }

Block* Block :: getNextBlock()	{ return next_block ; }



//MUTATORS

void Block :: setFree( bool free )		
{
	this -> free = free ;
}


void Block :: setSize( int size )
{
	this -> size = size ;
}


void Block :: setBlockID( int blockID )
{
	this -> blockID = blockID ;
}

//OPERATOR OVERLOADERS

ostream& operator << ( ostream& os , Block* block )
{
	os   << "ID:"
		 << TAB
		 << block -> getBlockID()
		 << TAB
		 << TAB ;
	
	if ( block -> isFree() )
	{
		os << "FREE" ;
	}
	
	else 
	{
		os << "IN USE" ;
	}
	
	os	 << NL
		 << "Size:"
		 << TAB
		 << TAB
		 << block -> getSize() ;
		
	return os ;
}
