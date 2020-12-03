#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

char* hexlify(char* string)
{
	char* hex;
	for(int i = 0; i < strlen(string); i++)
	{
		char temp[5];
		sprintf(temp, "%X", word[i]);
		strcat(hex,temp);
	}

	return hex;
}

char* stripTrail(char* a_str, size_t ln)
{
	// Strip trailing newline
	if (a_str[ln] == '\n') a_str[ln] = '\0';

	return a_str;
}

bool startsWith(const char* a_str, const char* delim)
{
	for (size_t i = 0; delim[i] != '\0'; i++){
		if (a_str[i] != delim[i])
			return false;
	}
	return true;
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

int endsWith (char *str, char *end) {
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
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}

		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}