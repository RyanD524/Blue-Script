#include <stdio.h>
#include <string.h>
#include "BS_Lib.h"
/*¯\_(ツ)_/¯*/
// ^^ Here for "professionalism" 
/*
	Notes: HEX -> ASCII
	not working yet 
*/
int main(int argc, char *argv[]){
	
	if (argc < 2)
	{
		printf("Don't forget to pass arguments!\n");
		return -1;
	}

	char* filename = argv[1];
	
	if (endsWith(filename, ".blc")) {
		readCmds(filename);
	} else {
		printf("Incorrect file type");
		return -2;
	}
}