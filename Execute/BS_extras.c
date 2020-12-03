#pragma once

#include <stdio.h>
#include <stdlib.h>

int inList(int val, int* arr, int len)
{
	for(int i = 0; i < len; i++)
	{
		if(*(arr + i) == val)
			return 1;
	}
	return 0;
}


/*int hash(const char *str)
{
	int result = 0x55555555;;

	while (*str)
	{
		result ^= *str++;
		result = rol(result, 5);
	}

	return result;
}*/


int isLocalVar(char* str)
{
	/*
		Check if a string is a key anywhere
		and if it is a var
	*/
	return 0;
}