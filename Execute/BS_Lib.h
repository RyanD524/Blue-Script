#include "BS_tuple.c"
#include "BS_Hex.c"
//#include "BS_dict.c"
#include "BS_string.c"
#include "BS_Runner.c"
#include "BS_core.c"
#include "BS_extras.c"
#include "BS_Execute.c"
//#include "BS_memory.c"
#include "BS_types.h"

//BS_string.c
int charFreq(char* string, char lookfor);
int isInt(char* a_str);
int endsWith (char *str, char *end);
int len(char* str);
int argLen(char* str, int index1, int index2);
char** str_split(char* a_str, const char a_delim);
char* strmov(char* str);
char* stripTrail(char* a_str, size_t ln);
char* append(const char* str, const char c);
bool compair(char* str, char* str2);
bool startsWith(const char* a_str, const char* delim);
bool contains(char* string, char delim);
void *_allocator(size_t element, size_t typeSize);
void hexlify(char* input, char* output);

// BS_extras.c
int inList(int val, int* arr, int len);
char* ChangeNS(char* arg);


// BS_Execute.c
void callFunc(char* args);
void funcsetup(int opCode);

//BS_Hex.c
int hex_to_int(char c);
int hex_to_ascii(char c, char d);