#pragma once 

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp
#include "BS_Lib.h"

#define BUF 128
#define TOT 10


char* CNS = "main";
char* expected;
int* excludedLines;

static void Pre_Execute(char* cmd)
{
	char* test = hexlify("hello");
	printf("%s\n", test);
	int* opCode;
	char** splitStr = str_split(cmd, ':');
	if (!strcmp(*(splitStr + 0), "CALL_FUNC"))
	{
		opCode = (int*)*(splitStr + 1);
		expected = "args";
	}

	if(!strcmp(*(splitStr + 0), "args") && expected == "args")
	{
	}
}

static void splitEnv(char line[TOT][BUF], int total)
{
	int pos = 0;
	excludedLines = calloc(200, sizeof(int)); // int array 200
	// reads through and gets all namespaces
	// places all 
	char** tk;
	for(int i = 0; i < total; i++)
	{
		if (startsWith(line[i], "NAMESPACE"))
		{
			tk = str_split(line[i], '-');
			addTuple(*(tk + 1), i+1);
			*(excludedLines + pos) = i;
			pos++;
			free(tk);
		}
	}

	int index = getTuple(CNS);
	int tcount;
	//int tmpIn;
	while (true)
	{
		//tmpIn = 0;
		if(inList(index,excludedLines,pos))
		{
			if (CNS == "main")
				exit(0);

			else
			{
				CNS = "main";
				index = getTuple(CNS);
			}
		}

		tcount = charFreq(line[index], '~');
		tk = str_split(line[index], '~');

		for(int j = 0; j <= tcount; j++)
		{
			Pre_Execute(*(tk + j));

		}


		index++;
	}
}


void readCmds(char *filename)
{
	char line[TOT][BUF];
	char* CNS;
	FILE *plist = NULL;
	int i = 0;
	int total = 0;

	plist = fopen(filename, "r");

	while(fgets(line[i], BUF, plist)) {
		line[i][strlen(line[i]) - 1] = '\0';
		i++;
	}
	
	total = i;
	splitEnv(line, total);

	if (line)
		free(line);

	return;
}