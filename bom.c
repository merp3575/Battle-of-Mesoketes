/* 
	Project : Battle of Mesoketes
	Author  : Premkumar
	Date    : 8/7/2017
*/

#include "bom.h"

int main()
{
	//init stregth and success count variables
	init();
	
	/*
	    start the program execution
	    parameters:
		input file name where we read the input cases
		output file name where the ouput gonna store
		Testcase results object
	*/
	start("input.txt","output.txt",results);
	return 0;
}
