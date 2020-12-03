#pragma once

#include "BS_Lib.h"

int nestedExpected = 0;

// CALL_FUNC
// thrid
void funcCall()
{

}
// second 
void argParse(char* args)
{
	return;
}

// tech first
int checker()
{
	if (*inIf == true)
	{
		if (nestedExpected == 0)
			nestedExpected = 1;
	}
	else
		nestedExpected = 0;
}

// first 
void load_func(int* opCode)
{
	checker();
	switch (*opCode)
	{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;


	}
}