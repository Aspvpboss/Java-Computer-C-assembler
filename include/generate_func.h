#pragma once
#include "common.h"

char* strint(int num);
char* generate_opcode(int num_bytes, int opcode);


int generate_alu_1_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3);
int generate_alu_1(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3);
int generate_alu_2(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4);
int generate_alu_2_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4);