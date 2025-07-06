#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>



//every opcode 
typedef enum{

    NONE,
    LABEL_STRING,
    LABEL_INT,
    HLT_DIRECT,
    NOP_DIRECT,
    ALU_1,
    ALU_1_IMMEDIATE,
    ALU_1_FLAG,
    ALU_1_IMMEDIATE_FLAG,
    ALU_2,
    ALU_2_IMMEDIATE,
    ALU_2_FLAG,
    ALU_2_IMMEDIATE_FLAG,
    LDI_DIRECT,
    LDI_INDIRECT_3,
    CTC_DIRECT,
    CTC_INDIRECT_2,
    CTC_INDIRECT_3,
    RTR_DIRECT,
    RTR_INDIRECT_2,
    RTR_INDIRECT_3,
    RTP_DIRECT,
    RTP_INDIRECT_2,
    CTR_DIRECT,
    CTR_INDIRECT_2,
    CTR_INDIRECT_3,
    CTR_INDEX,
    RTC_DIRECT,
    RTC_INDIRECT_2,
    RTC_INDIRECT_3,
    RTC_INDEX,
    PSH_DIRECT,
    PSH_INDIRECT_2,
    POP_DIRECT,
    POP_INDIRECT_3,
    CLD_DIRECT,
    CLD_INDIRECT_2,
    CST_DIRECT,
    CST_INDIRECT_2,
    XLD_DIRECT,
    XLD_INDIRECT_2,
    XLD_INDIRECT_3,
    XST_DIRECT,
    XST_INDIRECT_2,
    XST_INDIRECT_3,
    SND_DIRECT,
    SND_INDIRECT_2,
    SND_INDEX,
    REC_DIRECT,
    REC_INDIRECT_3,
    REC_INDEX,
    WRE_DIRECT,
    WRE_INDIRECT_3,
    WRE_INDEX,
    JMP_DIRECT,
    JMP_INDIRECT_3,
    JIF_DIRECT,
    JIF_INDIRECT_2,
    JIF_INDIRECT_3,
    CAL_DIRECT,
    CAL_INDIRECT_3,
    CIF_DIRECT,
    CIF_INDIRECT_2,
    CIF_INDIRECT_3,
    RET,
    
} Opcode_Type;



//every first assembler argument
typedef enum{

    ERROR,
    SIZEOF,
    LABEL,
    AT_ADDRESS,
    SET_CONSTANT,
    SECTION_DATA,
    SECTION_TEXT,
    HALT,
    NO_OP,
    ALU_OP,
    COMPARE,
    JUMP,
    JUMP_IF,
    CALL,
    CALL_IF,
    RETURN,
    MOVE,
    CACHE_LOAD,
    CACHE_STORE,
    EXTERNAL_LOAD,
    EXTERNAL_STORE,
    PUSH,
    POP,
    SEND,
    WAIT_RECEIVE,
    RECEIVE,

} Assembler_Arguments;


//condition to check for in check_immediate()
typedef enum{
    
    DECIMAL_IMMEDIATE,
    HEXADECIMAL_IMMEDIATE,
    BINARY_IMMEDIATE,
    CACHE_ADDRESS,
    PAGE_ADDRESS,
    ANY_IMMEDIATE

} Immediate_Mode;


//condition to check for in check_cache() or check_register()
typedef enum{
    
    DIRECT_ADDRESSING,
    INDIRECT_ADDRESSING,
    INDEX_ADDRESSING,
    ANY_ADDRESSING

} Address_Mode;


//used to make indexing tokens readable
typedef enum{

    TOKEN_ONE,
    TOKEN_TWO,
    TOKEN_THREE,
    TOKEN_FOUR,
    TOKEN_FIVE

} Token_Select;








#define MAX_BYTES 1024

typedef struct{

    FILE *file_in;
    FILE *file_out;
    int file_lines;

    //first index is for lines of file, second is for tokens, third is for characters of the token
    char ***file_arrays;
    int file_array_size;

    char **output_arrays;

} File_Info;
extern File_Info f;



typedef struct{

    //each index is for number of tokens for the line 
    int *num_tokens;
    //each index is number of bytes for the line
    int *num_bytes;
    //each index is instruction type for the line
    Assembler_Arguments *instruction_array;

    Opcode_Type *opcode_array;

} Token_Info;
extern Token_Info t;



typedef struct{

    char **label_strings;
    int *label_addresses;
    int num_labels;
    int total_bytes;

} Label_Info;
extern Label_Info l;



typedef struct{
    //stores name of macro aka 'TEMP_CHAR'
    char **macro_name;
    //literal macro aka 'r0' or 'io0'
    char **macro;
    int num_macros;

} Set_Vars;
extern Set_Vars set;

#include "init.h"
#include "tokenize.h"
#include "parse.h"
#include "arguments.h"
#include "get_bytes.h"
#include "generate.h"