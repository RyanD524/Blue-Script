#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BS_Lib.h"

static int opcode;

char** tk;

void callFunc(char* args)
{
	char* tmpStr;
	char buf = 0;
	int len = charFreq(args, ',') + 1;
	int tmpVal;
	int type;



	tk = str_split(args, ',');
	for(int i = 0; i < len; i++)
	{
		tmpStr = *(tk + i);
		type = argLen(tmpStr, BS_TYPE_B1, BS_TYPE_B2);
		//printf("%s\n", tmpStr);		
		for(int j = 0; j < argLen(tmpStr, BS_ARG_LEN, BS_ARG_LEN1) * 2; j++)
		{
			if (j % 2 != 0)
			{
				tmpVal = hex_to_ascii(buf, tmpStr[j + 4]);
				//printf("%c\n", tmpVal);
				//printf("%i\n", tmpVal);
			}
			else if (j % 2 == 0)
				buf = tmpStr[j+4];
		}
	}


	free(tk);
}

void funcsetup(int opCode)
{
	opcode = opCode;
}