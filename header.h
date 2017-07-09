/* 
	Project : Battle of Mesoketes
	Author  : Premkumar
	Date    : 8/7/2017
*/

#include<stdio.h>

/*
	Size of buffer where we store the file input. 
	It will have one day battle details at a time
	Example:Day 1; T1 - S - 4: T1 - N - 2: T3 - W - 3
*/ 
#define bufferSize 200

//Temporary usage string size
#define tempSize   50

//Total Directions count. North, East, West, South. Total 4
#define direction_count  4

//Total number of days
#define day_count 3

//number of unit test case 
#define testCase_count 8


/*
	To store directions strength details.
	Index 0 for north
	Index 1 for east
	Index 2 for west
	Index 3 for south
*/
int dir[direction_count];

enum directions {
	NORTH,
	EAST,
	WEST,
	SOUTH
};


/*
	To maintain temporary strength details. 
	Becuase at the end of the day only we are going to update the wall strength
*/
int temp[direction_count];

//Final success count will be stored here
int success_count;

/*
	structure to store unit test case name and expected results
*/
struct unitTest
{
	char name[bufferSize];
	int output;
};

struct unitTest results[testCase_count] ={
				 	{"Sample testcase1",                                   6},
				 	{"Sample testcase2",                                   6},
				 	{"All Zero inputs",                                    0},
				 	{"All negative inputs",                                0},
				 	{"Same direction in a whole day",                      10},
				 	{"Mixing positive,negative and same direction attack", 13},
				 	{"Same direction in all 3 days",                       7},
				 	{"Large valued strengths",                             5}
					 	
				 };

//It will initialize wall strength initially zero and also the success count
void init();

//Input will be given using a file. This function will process the file
void start(char *inputFile,char *outputFile,struct unitTest *ExpectedOutputs);

/*
	Used to extract each tribe deatils separately using ':' delimiter
	Example:
	input:
	Day 1: T1 - N - 3: T2 - S - 4: T3 - W - 2
	output:
	Day 1
	T1-N-3
	T2-S-4
	T3-w-2
*/
void splitStringByColon(char *str);

/*
	This function will extract direction and strength details from each tribe
	Example:
	input  : T1 - N - 3
	output : 
	Direction = N
	strength = 3 
*/
void getDirectionAndStrength(char *str);

//This will update each tribe details into temporary strength array
void updateShadowHeights(char direction,int strength);

//After end of the day, Normalized strength details will be updated by this function
void updateOriginalHeights();

//unit test case results
void unitTestResults(int output,int test_count,struct unitTest *expectedOutput);
