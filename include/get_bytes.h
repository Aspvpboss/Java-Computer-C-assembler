#pragma once 
#include "common.h"
int get_text_bytes(Assembler_Arguments instruction, char **p_string, int MAX_TOKENS, int c_line, Opcode_Type *opcode);
int get_data_bytes(Assembler_Arguments instruction, char **p_string, int MAX_TOKENS, int c_line, Opcode_Type *opcode);