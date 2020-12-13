#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // strcmp
#include "BS_Lib.h"

#define BUF 128
#define TOT 10

char** splitStr;
char* CNS = "main"; // current namespace
char* PE_tmp;
int* excludedLines;
int changeCNS = 0;
int opCode;

static void Pre_Execute(char* cmd)
{
	splitStr = str_split(cmd, ':');
	if (!strcmp(*(splitStr + 0), "CALL_FUNC"))
	{
		PE_tmp = *(splitStr + 1);
		opCode = (int)*PE_tmp - 48;
		if (opCode == BS_CALL)
			changeCNS = 1;

		else
		{
			funcsetup(opCode);
		}
	}


	if(!strcmp(*(splitStr + 0), "args"))
	{
		if (changeCNS == 1)
		{
			CNS = ChangeNS(*(splitStr + 1));
			changeCNS = 0;
		}
		else
		{
			callFunc(*(splitStr + 1));
		}
	}
}

static void splitEnv(char line[TOT][BUF], int total)
{
	bool newIndex = false;
	int inIf = 0;
	int pos = 0;
	int len = 0;
	int index;
	int tcount;
	
	excludedLines = calloc(200, sizeof(int)); // int array 200
	
	char* LNS; // last name space
	// reads through and gets all namespaces
	// places all 
	char** tk1;
	char** tk2;
	for(int i = 0; i < total; i++)
	{
		//printf("%s\n", line[i]);
		if (startsWith(line[i], "NAMESPACE"))
		{
			tk1 = str_split(line[i], '-');
			addTuple(*(tk1 + 1), i+1);
			*(excludedLines + pos) = i;
			pos++;
			free(tk1);
		}
		len++;
	}
	index = getTuple(CNS);
	while (true)
	{
		if (CNS != LNS)
		{
			index = getTuple(CNS);
		}
		if(index > len - 1) // index out of range (note issue clean exit)
			exit(0);

		if(inList(index,excludedLines,pos))
		{
			if (CNS == "main")
				exit(0); // EOF

			else
			{
				CNS = "main";
				index = getTuple(CNS);
			}
		}

		tcount = charFreq(line[index], '~');
		tk2 = str_split(line[index], '~');

		if(!strcmp(*(tk2 + 2),"nest:False") && inIf == 0 || !strcmp(*(tk2 + 2),"nest:True") && inIf == 1)
		{
			for(int j = 0; j <= tcount - 1; j++)
			{
				Pre_Execute(*(tk2 + j));
			}
		}
		LNS = CNS;
		free(tk2);
		index++;
	}

	free(tk1);
	free(splitStr);
	free(PE_tmp);
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