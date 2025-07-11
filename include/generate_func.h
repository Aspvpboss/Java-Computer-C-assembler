#pragma once
#include "common.h"

char* strint(int num);
char* generate_opcode(int num_bytes, int opcode);

// ALU instructions
int generate_alu_1_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3);
int generate_alu_1(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3);
int generate_alu_2(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4);
int generate_alu_2_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4);

// MOV instructions
int generate_ldi(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);
int generate_rtr_ctc_rtc_ctr(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);
int generate_rtp(int opcode, int c_bytes, int total_bytes, char *tk_2);

// data stack instructions
int generate_psh(int opcode, int c_bytes, int total_bytes, char *tk_2);
int generate_pop(int opcode, int c_bytes, int total_bytes, char *tk_2);

// RAM instructions
int generate_cld_cst(int opcode, int c_bytes, int total_bytes, char *tk_2);
int generate_xld_xst(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);

// IO instructions
int generate_snd(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);
int generate_rec(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);

// data labels
int generate_label_int(int opcode, int c_bytes, int total_bytes, char *tk_3);
int generate_label_string(int opcode, int c_bytes, int total_bytes, char *tk_3);

// control flow
int generate_jmp(int opcode, int c_bytes, int total_bytes, char *tk_2);
int generate_jif(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3);