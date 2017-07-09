/* 
	Project : Battle of Mesoketes
	Author  : Premkumar
	Date    : 8/7/2017
*/

#include "header.h"

/*
	This function will read the given input file.
	Each Day data will be sent to further processing
	once a complete day tribes are over, 
	Results will be updated to direction strength array
*/

void start(char *inputFile,char *outputFile,struct unitTest *ExpectedOutputs)
{
	int count = 0,testcase_count = 0;
	FILE *inputReader = NULL;     //File pointer. Initially pointing to NULL
	FILE *outputWriter = NULL;   //File writer
	char buffer[bufferSize];    // Buffer is used to store a line from file
	char output[tempSize];
	
	inputReader = fopen(inputFile,"r"); //opening input file with reading mode
	outputWriter = fopen(outputFile,"w"); //opened output file to update results
	
	if(inputReader) // if file found proceed.
	{
		//read the file line by line using fgets funtion.
		while(fgets(buffer,bufferSize,inputReader)) 
		{
			count++;
			splitStringByColon(buffer); //send the line to split each tribe details
			updateOriginalHeights();   //After a day, wall strength will be updated 
			
			if(count % day_count == 0) // it will be true if one input case (all 3 days) data are processed.
			{
			
			    //update UT results
			    unitTestResults(success_count,testcase_count,&ExpectedOutputs[testcase_count]);
				/*
					To store data into file using fputs, data should be string format.
					converting integer to string using sprintf which will print given data to buffer.
					Here buffer is string. So int will be converted to string.
				*/
				sprintf(output,"%d\n",success_count); 
				fputs(output,outputWriter); //write output to file
				init(); //reset all variables
				count = 0; //reset the counter.
				testcase_count++;      //it will increment once a testcase finished
			}
		}
	}
	
	//deallocate file pointers
	fclose(inputReader);
	fclose(outputWriter);
}

/*
Initially, each side wall strength is zero.
setting both original and shadow wall strengths as zero.
*/
void init()
{
	int i;
	for(i=0;i<direction_count;i++)
	{
		dir[i] = 0;
		temp[i] = 0;
	}
	success_count = 0; //setting success count as zero initially
}

/*
This function will split the line using ':' delimiter.
Each delimiter will send to another function which will split strength and direction deatils.
Here, skipcount used to avoid processing Day 1, Day 2, Day 3 strings.
Spaces will be avoided here.
*/
void splitStringByColon(char *str)
{
	char temp[tempSize];
	int i,count = 0,skipCount = 0;
	
	for(i=0;str[i];i++)
	{
		if(str[i] != ':')
		{
			if(str[i] != ' ') //avoiding space
	        	temp[count++] = str[i];
	        
	    }
	    else
	    {
	        temp[count] = '\0';
	        skipCount++; // if skip count is 1, it will have day details. there is no need to process day details.
	        if(skipCount > 1)
	            getDirectionAndStrength(temp);
	        
	        count = 0;
	    }
	}
	//final tribe details
	temp[count] = '\0';
	//Each tribe details will be send to getDirectionAndStrength function 
	getDirectionAndStrength(temp);
}

/*
	This function will split direction and strength details from tribe.
	Flag is used to avoid processing tribe deatils. Like T1, T3.
	Strength and Direction details will be updated to temporary array.
	
	input:
	T1-N-3
	output:
	Direction = N
	Strength = 3
*/
void getDirectionAndStrength(char *str)
{
	int i,Strength;
	int flag = 0,count = 0;
	char temp[tempSize],Direction;
	
	for(i=0;str[i];i++)
	{
		if(str[i] == '-' && flag == 0)
		{
			flag = 1;
			Direction = str[i+1]; //Direction will be next to '-' char
			i+=3;                 //moving to strength part which 3 char apart from '-'
		}
		if(flag == 1)
			temp[count++]=str[i];
	}
	temp[count]='\0';
	Strength = atoi(temp); // converting string to integer using atoi function
	
	updateShadowHeights(Direction,Strength); //updating result to temporary array
}

/*
This function will check direction and update the corresponding value.
If two or more attack happened in same day, we have to keep the largest one
Hence we are using temporary array which will keep the largest value.

Each time attack occurs, we will increment success_count variable
*/
void updateShadowHeights(char direction,int strength)
{	
	if(direction == 'N' || direction == 'n')
	{
		if(strength > dir[NORTH])
		{
			temp[NORTH] = strength;
			success_count++;
		}
	}
	if(direction == 'E' || direction == 'e')
	{
		if(strength > dir[EAST])
		{
			temp[EAST] = strength;
			success_count++;
		}
	}
	if(direction == 'W' || direction == 'w')
	{
		if(strength > dir[WEST])
		{
			temp[WEST] = strength;
			success_count++;
		}
	}
	if(direction == 'S' || direction == 's')
	{
		if(strength > dir[SOUTH])
		{
			temp[SOUTH] = strength;
			success_count++;
		}
	}
}

/*
	After a day, normalized result will be updated to original array.
	if temporary value is higher than original, update the original array
	else leave it. 
*/
void updateOriginalHeights()
{
	if(dir[NORTH] < temp[NORTH])
		dir[NORTH] = temp[NORTH];
	if(dir[EAST] < temp[EAST] )
	    dir[EAST] = temp[EAST];
	if(dir[WEST] < temp[WEST])
	    dir[WEST] = temp[WEST];
	if(dir[SOUTH] < temp[SOUTH])
	    dir[SOUTH] = temp[SOUTH];
	
	//reset the temporary array value to zero
	temp[NORTH]=temp[EAST]=temp[WEST]=temp[SOUTH]=0;
}


/*
	It will check the expected and original output and then update the results in console
*/
void unitTestResults(int output,int test_count,struct unitTest *expectedOutput)
{
	printf("Name:\t%s\n",expectedOutput->name); //test case name
	
	if(!(output ^ expectedOutput->output)) //checking for expected and program output are same
		printf("Result:\tPassed\n\n");
	else
		printf("Result:\tFailed\n\n");
		
	printf("-----------------------------------------------------------\n\n");
}
