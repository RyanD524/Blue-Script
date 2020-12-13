#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BS_Lib.h"

int inList(int val, int* arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		if(*(arr + i) == val)
			return 1;
	}
	return 0;
}

char* ChangeNS(char* arg)
{
	int inName = 0;
	int hasName = 0;
	char* returnVal = "";
	char buf = 0;
	char tmp;
	int len = argLen(arg,BS_ARG_LEN,BS_ARG_LEN1);
	//printf("%i\n", argLen(arg));

	for (int i = 0; i < sizeof(arg); i++)
	{
		if(arg[i] == '\'' && hasName == 0)
		{
			if (inName == 0)
				inName = 1;
			else
				hasName = 0;
		}

		else if (arg[i] != '\'' && inName == 1)
		{
			tmp = arg[i];
			returnVal = append(returnVal, tmp);
		}

	}
	return returnVal;
}