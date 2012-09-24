
/*
 Memory Allocation List Simulator
 main.cpp
 
 main() program file
 
 SOPHIE DAVISON
 March 2011
 
 */


#include <iostream>
#include <string>
#include <cctype>
#include <list>
#include <stdlib.h>

#include "Block.h"
#include "MemoryList.h"
#include "MAL_operation.h"
#include "definitions.h"

using namespace std ;

string noSpaces( string menu_option ) ;

char getFirstLetter( string menu_option_no_spaces ) ;

bool validNumbers( string menu_option_no_spaces ) ;

int getNumbers( string menu_option_no_spaces ) ;

void printMenu() ;

void prompt() ;

//--------------------- MAIN ------------------------------

int main()
{
    MemoryList MemoryAllocationList ;
    
    list< MAL_operation > log ;
    list< MAL_operation > :: iterator log_itr ;
    
    char menu_choice ;
    int temp_n = 0 ; //bID or size of block to allocate
    
    string menu_option ;
    string menu_option_no_spaces ;
    
    printMenu() ;
    
    for ( ; menu_choice != QUIT ; )
    {
        
        prompt();
        getline( cin , menu_option ) ;
        
        if( menu_option == "")
        {
            menu_option = DEFAULT_STRING ;
        }
        
        
        menu_option_no_spaces = noSpaces( menu_option ) ;
        menu_choice = getFirstLetter( menu_option_no_spaces ) ;
        
        if( validNumbers(menu_option_no_spaces) )
        {
            temp_n = getNumbers( menu_option_no_spaces ) ;
        }
        else
        {
            temp_n = 0 ; //list bIDs start at 0
        }
        
        switch ( menu_choice )
        {
            case ALLOCATE :
                
                if ( MemoryAllocationList . allocateBlock( temp_n ) )
                {
                    MAL_operation operation( "allocated block of size ", temp_n ) ;
                    log . push_back( operation ) ;
                    
                    cout << "Allocation sucessful.  Block ID "
                    << MemoryAllocationList . getLastBlockID()
                    << ", size: "
                    << temp_n
                    << endl ;
                }
                
                else
                {
                    cout << "Unable to allocate that amount of memory"
                    << endl;
                }
                
                break ;
                
                
                
            case RELEASE :
                
                if ( MemoryAllocationList . releaseBlock( temp_n ) )
                {
                    MAL_operation operation( "released block ", temp_n ) ;
                    log . push_back( operation ) ;
                    
                    cout << "Release sucessful"
                    << endl ;
                }
                
                else
                {
                    cout << "Cannot release that block"
                    << endl ;
                }
                
                break ;
                
                
                
            case PRINT :
                
                cout << MemoryAllocationList ;
                
                break ;
                
                
            case QUIT :
                
                if( ! log . empty() )
                {
                    cout << "Chronological list of operations:"
                    << NL ;
                    
                    
                    for ( log_itr = log . begin() ; log_itr != log . end() ; log_itr++ )
                    {
                        cout << log_itr -> operation
                        << log_itr -> temp_n
                        << endl ;
                    }
                }
                
                else  // if log empty
                {
                    cout << "List of operations is empty."
                    << endl ;
                }
                
                cout << NL;
                break;
                
                
            default:
                cout << "Not a valid menu choice, enter another: "
                << endl ;
        }
    }
    
    
}
//-----------------------------------------------------------------------

// function to take out spaces in user input string
string noSpaces(string menu_option)
{
    string menu_option_no_spaces ;
    char menu_option_default = 'd' ;
    
    for( int i = 0 ; i < menu_option.size() ; i++)
    {
        if( menu_option . at( i ) != SPACE )
        {
            menu_option_no_spaces += menu_option . at( i ) ;
        }
    }
    return menu_option_no_spaces ;
}

// takes the first letter of the input string (with no spaces)
char getFirstLetter( string menu_option_no_spaces )
{
    char menu_choice ;
    
    menu_choice = menu_option_no_spaces . at( 0 ) ;
    menu_choice = tolower( menu_choice ) ;
    
    return menu_choice ;
}

/* discards the first char and evaluates whether the remaining
 * string (without spaces) are int(s) */
bool validNumbers( string menu_option_no_spaces )
{
    string menu_option ;
    
    menu_option = menu_option_no_spaces . substr( 1 ) ;
    
    for( int i = 0 ; i < menu_option . size() ; i++ )
    {
        if( ! isdigit( menu_option . at( i ) ) )
        {
            return false ;
        }
    }
    
    return true ;
}

/* discards the first char and converts the remaining string
 * to int(s) */
int getNumbers( string menu_option_no_spaces )
{
    int temp_n ;
    string menu_option;
    
    menu_option = menu_option_no_spaces . substr( 1 ) ;
    
    temp_n = atoi( menu_option . c_str() ) ;
    
    return temp_n ;
}


// prints menu choices
void printMenu()
{
    cout    << NL
    << "Memory Allocation Menu: "
    << NL
    << TAB
    << "a n : Allocate a block of size n"
    << NL
    << TAB
    << "r n : Release block with block ID n"
    << NL
    << TAB
    << "p   : Print a current memory map"
    << NL
    << TAB
    << "q   : Quit and display a history of the memory allocation and release"
    << NL ;
}

// prompt user to input string for menu selection
void prompt()
{
    cout << NL
    << "Enter your choice > " ;
}



