#pragma once

void BS_ErrorHandler(char* details, int errorCode)
{
	// error handling
	exit(errorCode);
}
