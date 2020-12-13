#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "BS_Lib.h"

#define MIN_STR_LEN 1 
#define MAX_STR_LEN 99
#define NUM_STR 200
#define ERR_MESSAGE__NO_MEM "Not enough memory!"
#define allocator(element, type) _allocator(element, sizeof(type))

int len(char* str) { return strlen(str); }
/** Allocator function (safe alloc) */
void *_allocator(size_t element, size_t typeSize)
{
    void *ptr = NULL;
    /* check alloc */
    if( (ptr = calloc(element, typeSize)) == NULL)
    {printf(ERR_MESSAGE__NO_MEM); exit(1);}
    /* return pointer */
    return ptr;
}


int argLen(char* str, int index1, int index2)
{
	int endNum = 0;
	char num1 = str[index1];
	char num2 = str[index2];
	if (num1 != '0')
		endNum = (int)num1 * 10 - 48;
	endNum += (int)num2 - 48;

	return endNum;
}

char* strmov(char* str)
{
	int i;
	char buf = 0;
	for (i = 0; i < len(str); i++)
	{
		if(i % 2 != 0)
			printf("%c\n", hex_to_ascii(buf, str[i]));
		else
			buf = str[i];
	}

}

void hexlify(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}

char* stripTrail(char* a_str, size_t ln)
{
	// Strip trailing newline
	if (a_str[ln] == '\n') a_str[ln] = '\0';

	return a_str;
}

char* append(const char* str, const char c)
{
	char* newString, *ptr;
	newString = allocator((strlen(str) + 2), char);
	ptr = newString;

	for(; *str; str++) {*ptr = *str; ptr++;}

		*ptr = c;

	return newString;

}

bool compair(char* str, char* str2)
{
	for(int i = 0; i < strlen(str); i++)
	{
		if(str[i] != str2[i])
			return false;
	}
	return true;
}

bool startsWith(const char* a_str, const char* delim)
{
	for (int i = 0; delim[i] != '\0'; i++){
		if (a_str[i] != delim[i])
			return false;
	}
	return true;
}

bool contains(char* string, char delim)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] == delim)
			return true;
	}
	return false;
}

int charFreq(char* string, char lookfor)
{
	int count = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		if(string[i] == lookfor)
			count++;
	}

	return count;
}

int isInt(char* a_str)
{
	// is int == 1
	// is float == 2
	// is not int = 0
	int dotcount = 0;
	for(int i = 0; i < strlen(a_str); i++)
	{
		//ASCII value of 0 = 28, 9 = 57.
		// so if outside of range then numer is not int
		//checking for negative sign "-" could be added: ASCII value 45
		if (a_str[i] <45 || a_str[i] > 57)
			return 0;
		if (a_str[i] == '.')
			dotcount ++;
	}
	if (dotcount != 1)
		return 1;
	else if (dotcount == 1)
		return 2;
	else
		return 0;
}

int endsWith (char *str, char *end) 
{
    size_t slen = strlen (str);
    size_t elen = strlen (end);
    if (slen < elen)
        return 0;
    return (strcmp (&(str[slen-elen]), end) == 0);
}

char** str_split(char* a_str, const char a_delim)
{
	char** result = 0;
	size_t count = 0;
	size_t idx = 0;
	char* tmp = a_str;
	char* last_delm = 0;
	char delim[2];
	
	delim[0] = a_delim;
	delim[1] = 0;

	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count ++;
			last_delm = tmp;
		}
		tmp++;
	}

	count += last_delm < (a_str + strlen(a_str) -1 );
	count ++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}

		if(idx >= MIN_STR_LEN)
		{
			assert(idx == count - 1);
			*(result + idx) = 0;
			return result;
		}
	}
}