
/*
 Memory Allocation List Simulator
 MemoryList.h
 
 Memory List HEADER FILE
 
 DAVID SAUNTSON 
 March 2011
 
 */


#include "Block.h"

#include <iostream>
#include <list>

using namespace std ; 

class MemoryList 
{
	
	friend ostream& operator<< ( ostream& os , MemoryList ) ;
	
public:
	
	//CONSTRUCTOR
	MemoryList() ;	
	
	//ACCESSORS
	bool isEmpty() ;
	bool isValidBlockID( int bID ) ;
	bool isValidBlockSize( int size ) ;
	
	int nextBlockID() ;
    int getLastBlockID() ;
	
	Block* getFirst() ;
	Block* getBiggestFreeBlock() ;
	
	
	//MUTATORS
	
	void setBiggestFreeBlock() ;
	
	void insertFirst( Block* newBlock ) ;
	void insertAfter( Block* block , Block* newBlock ) ;
	
    bool coalescePrevious( Block* released_block ) ;  
    //coalesces released_block with released_block -> prev_block
	
	bool releaseBlock( int blockID ) ;
    //sets free to false, checks neighbours & coalesces if req'd
	
    bool allocateBlock( int size ) ;
    //allocates using worst fit
			
	
private:
	
	Block* first ;
	Block* biggestFreeBlock ;
	
    int maxMemory ;          
    int minBlockSize ;
	int lastBlockID ;
	
	list< int > invalidBIDs ;				
    //maintains list of invalid block IDs for input validation
    
	list< int > :: iterator invBID_itr ;	
    //invalid block ID list iterator

} ;
