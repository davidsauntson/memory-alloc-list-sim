
/*
 Memory Allocation List Simulator
 definitions.h
 
 constants HEADER FILE
 
 DAVID SAUNTSON 
 March 2011
 
 */


using namespace std ;

const char ALLOCATE = 'a' ;
const char RELEASE = 'r' ;
const char PRINT = 'p' ;
const char QUIT = 'q' ;

const char NL = '\n' ;
const char TAB = '\t' ;
const char SPACE = ' ';

//this forms the arrow to indicate next block in memory map
const string BLOCK_SEPERATOR = "\n---------------------\n\t\t\t|\n\t\t\tV\n---------------------\n" ;

const string HORIZ_LINE = "\n---------------------\n" ;
const string ERROR_MESSAGE = "\nNot a valid input" ;
const string DEFAULT_STRING = "d" ; // this is default value if user doesn't enter anything

