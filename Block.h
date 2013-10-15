
/*
 Memory Allocation List Simulator
 Block.h
 
 Block HEADER FILE
 
 DAVID SAUNTSON 
 March 2011
 
 */

//here is a new comment.  OMG C++!

#include <iostream>
#pragma once 

using std :: ostream ;

class Block
{
	friend class MemoryList ;
	friend ostream& operator << ( ostream& , Block* ) ;
	
public:
	
	
	//ctors & dtors
	Block() ;	//default ctor
	Block( bool f , int s , int bID ) ;
	
	
	//accessors
	bool isFree() ;
	int getSize() ;
	int getBlockID() ;
	
	Block* getNextBlock() ;
	
	//mutators
	void setFree( bool ) ;
	void setSize( int ) ;
	void setBlockID( int ) ;
	
	
	
private:
	
	int blockID ;
	int size ;
	bool free ;
	
	Block* next_block ;
	Block* prev_block ;
	
} ;
