/*
 Memory Allocation List Simulator
 MemoryList.cpp
 
 Memory List IMPLEMENTATION FILE
 
 SOPHIE DAVISON ( allocateBlock() and setBiggestFree() )
 DAVID SAUNTSON ( everything else incl coalescePrevious() )
 March 2011
 
 */

#include <iostream>		//req'd for NULL

#include "MemoryList.h"
#include "Block.h"
#include "definitions.h"


//CONSTRUCTOR & DESTRUCTOR

MemoryList :: MemoryList()
{	
	lastBlockID = 1 ;
	minBlockSize = 1 ;
    maxMemory = 1024 ;
	
	first = new Block( true , maxMemory , lastBlockID ) ;
	biggestFreeBlock = first ;
    
    //add 0 to list of invalid bIDs
    invalidBIDs . push_back( 0 ) ;
    

	//create doubly linked list
    first -> next_block = first ;
	first -> prev_block = first ;
}


//ACCESSORS

bool MemoryList :: isEmpty()
{
	return first == NULL ;
}

bool MemoryList :: isValidBlockID( int bID )
{
	if ( bID > lastBlockID )
	{
		return false ;
	}
	
	if ( bID == first -> blockID	&&
        first -> free			     )
	{
		return false ;
	}
	
	for ( invBID_itr = invalidBIDs . begin() ; 
         invBID_itr != invalidBIDs . end()  ;
         invBID_itr++						 )
	{
		if ( bID == *invBID_itr )
		{
			return false ;
		}
	}
	
	return true ;
}

bool MemoryList :: isValidBlockSize( int possible_size )
{
	if ( possible_size < minBlockSize				||
        biggestFreeBlock == NULL					||
        possible_size > biggestFreeBlock -> size	 ) 
	{
		return false ;
	}
	
	return true ;
}


int MemoryList :: nextBlockID()
{
	lastBlockID += 1 ;
	return lastBlockID ;
}


int MemoryList :: getLastBlockID()
{
    return lastBlockID ;
}


Block* MemoryList :: getFirst()
{
	return first ;
}

Block* MemoryList :: getBiggestFreeBlock()
{
	return biggestFreeBlock ;
}


//MUTATORS



/* setBiggestFreeBlock scans each block in turn and compares it with 
 the biggest free block, changing it if necessary.  The second if statement 
 ensures biggestFreeBlock is set to NULL if there are no free blocks in 
 the list
 NOTE:  biggestFreeBlock is set as the first block on list instantiation */

void MemoryList ::  setBiggestFreeBlock()
{
	Block* current = first ;
	
	
	for ( ; current -> next_block != first ; )
	{
		if ( current -> free	&&
            current -> size > biggestFreeBlock -> size )
		{
			biggestFreeBlock = current ;
		}
        
		current = current -> next_block ;
	}
	
	if ( ! biggestFreeBlock -> free )
	{	
		biggestFreeBlock = NULL ;
	}
	
}

void MemoryList :: insertFirst( Block* newBlock ) 
{
	
	/* if/else statement ensures that the first and last blocks
     are only coalesced if they are the only two blocks in the
     list.  This is acheived by ensuring the coalescent
     block points to itself after the two blocks have been coalesced.*/
	
	
	if ( ( first -> next_block ) -> next_block == first )
    //ie if there is first and just one other being coalesced
	{
		newBlock -> next_block = newBlock ;
        ( first -> prev_block ) -> next_block = newBlock ;
        newBlock -> prev_block = first -> prev_block ;
        first = newBlock ;
        first -> prev_block = first ;  //single remaining block now points to itself
	}
	
	else 
	{
		newBlock -> next_block = ( first -> next_block ) -> next_block ;
        ( first -> prev_block ) -> next_block = newBlock ;
        newBlock -> prev_block = first -> prev_block ;
        first = newBlock ;
	}
}




void MemoryList :: insertAfter( Block* block , Block* newBlock )
{
	newBlock -> next_block = block -> next_block ;
	newBlock -> prev_block = block ;
	( block -> next_block ) -> prev_block = newBlock ;
	block -> next_block = newBlock ;
}


/*
 coalescePrevious creates a new block (coalescent_block) equal 
 to the sum of a given block (released_block) and its previous block.  
 The coalescent block is then inserted in the correct place depending 
 on whether the first block of the list is being coalesced or not.
*/
bool MemoryList :: coalescePrevious( Block* released_block )
{
	Block* coalescent_block = new Block ;
	
	if ( coalescent_block == NULL )
	{
		return false ;
	}
    
	else
	{
		coalescent_block -> setFree( true ) ;
		
		coalescent_block -> setBlockID( nextBlockID() ) ;
		
		//set size of new block to be total of released block + previous block
		coalescent_block -> size = 
         ( released_block -> size + ( released_block -> prev_block ) -> size ) ;
		
		
		//check to see if the released block is being coalesced with (or is) the first block
		if ( released_block -> prev_block == first ||
             released_block == first                )  

		{
			//insert the coalescent block at the start of the list
			insertFirst( coalescent_block ) ;
		}
        
		else
		{
			//insert the coalescent block before the released block's previous block
			insertAfter( ( released_block -> prev_block ) -> prev_block , coalescent_block ) ;
		}
        
        /* 
          update pointers of coalescent block when there is more than one block in the list
          can't do this in insert functions since the new block replaces two blocks (therefore
          pointers aren't updated in the same way.  This only needs to be done when there is
          more than two blocks left in the list.
        */
        
        if ( first -> next_block != first )
        {
            //change the coalescent block's next pointer to the block after the released_block
            coalescent_block -> next_block = released_block -> next_block ;
            
            //change the block after coalesced block prev pointer
            ( released_block -> next_block ) -> prev_block = coalescent_block ;
        }
        
        //add the blockIDs of the two coalesced blocks to the invalidBID list
		invalidBIDs . push_front( released_block -> blockID ) ;
		invalidBIDs . push_front( ( released_block -> prev_block ) -> blockID ) ;
		
		//delete the two coalesced blocks to prevent memory leak
		delete released_block -> prev_block ;
		delete released_block ;
		
		//check if biggestFreeBlock needs updating and update if necessary
		if ( coalescent_block -> size  > biggestFreeBlock -> size )
		{
			biggestFreeBlock = coalescent_block ;
		}
		
		return true ;
	}
}

bool MemoryList :: allocateBlock( int size ) 
{
	//determine whether there is a block of sufficient size for request
	if ( ! isValidBlockSize( size ) )
	{
		return false ;
	}
	
	else
	{
		Block* new_block = new Block ;
		
		if ( new_block == NULL			||
            ! biggestFreeBlock -> free  )
		{
			return false ;
		}
		
		else
		{
			//check of new block is exact size of biggest free block
			if ( biggestFreeBlock -> size == size )
			{
				//just change the used flag of biggest free
				biggestFreeBlock -> free = false ;
				
				setBiggestFreeBlock() ;
				
				return true ;
                
			}
			
			else
			{
				//populate new block data & insert into list
				new_block -> setSize( size ) ;
				new_block -> setFree( false ) ;
				new_block -> setBlockID( nextBlockID() ) ;
                
				insertAfter( biggestFreeBlock , new_block ) ;
				
				//adjust size of split block
				biggestFreeBlock -> size -= size ;
				
				//update biggest free block
				setBiggestFreeBlock() ;
				
				return true ;
                
			}
		}		
	}
}


bool MemoryList :: releaseBlock( int bID ) 
{	
	Block* target = first ;
		
	if ( ! isValidBlockID( bID ) )
	{
		return false ;
	}
    
	//find block for release and set as target
	for ( ; target -> blockID != bID ; )
	{
		target = target -> next_block ;
	}
	
	//handle case where entire list is alloc'd and bF is NULL
	if ( biggestFreeBlock == NULL )
	{
		biggestFreeBlock = target ;
		biggestFreeBlock -> free = true ;
	}
	
	//skip coalescence if there is only one block in list
	if ( target -> next_block == target )
	{
		target -> free = true ;
		return true ;
	}
    
	//create holding parameter for target -> next
	Block* neighbour = target -> next_block ;
	
	//release target and check if coalescence req'd
	target -> free = true ;
	
	if ( ( target -> prev_block ) -> isFree() &&
           target != first                      )
	{
		coalescePrevious( target ) ;
	}
            
    
	//check if target's neighbour is free and coalesce with new free block if required
	if ( neighbour -> isFree()  &&
         neighbour != first     &&
         first -> next_block != first )
	{
		coalescePrevious( neighbour ) ;
	}
	
	setBiggestFreeBlock() ;
	
	return true ;
	
}



//operator overloader

ostream& operator<< ( ostream& os , MemoryList list )
{
	Block* block = list . first ;
	
	os	<< HORIZ_LINE ; 
	
	do 
	{
		os	<< block ;
		
		if ( block -> getNextBlock() == list . first )
		{
			//at the end of the list so horizontal line req'd
			os	<< HORIZ_LINE ;
		}
		
		else
		{
			os	<< BLOCK_SEPERATOR ;
		}
        
		block = block -> getNextBlock() ;
		
	} while ( block != list . first ) ;
	
	return os ;
}


