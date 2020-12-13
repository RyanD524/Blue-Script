#pragma once

// Here for "professionalism"


// helpful
#define BS_META     4 // for args where the arg starts
#define BS_TYPE_B1  0 // for type casting byte 0
#define BS_TYPE_B2  1 // for type casting byte 1
#define BS_ARG_LEN  2 // for arglen byte 0
#define BS_ARG_LEN1 3 // for arglen byte 1
// types
#define BS_INT      0
#define BS_FLOAT    1
#define BS_STR      2
#define BS_BOOL     3
#define BS_VAR      4
#define BS_MATH_OP  5
#define BS_FUNC     6
#define BS_LOGIC_OP 7

// opcodes
#define BS_LET      1
#define BS_PRINT    2
#define BS_MATH     3
#define BS_IF       4
#define BS_END      5
#define BS_ARRAY    6
#define BS_CALL     7
#define BS_EXIT     8
#define BS_RETURN   9
#define BS_USE      10 // unused in compiled (just ref)
#define BS_GOTO     11 
#define BS_COMMENT  999 // unused in compiled (ref incase of accident ¯\_(ツ)_/¯)

