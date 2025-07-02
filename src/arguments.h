#pragma once
#include "common.h"

int check_cache(char *string, Address_Mode mode);
int check_reg(char *string, Address_Mode mode);
int check_reg_flags(char *string, Address_Mode mode);
int check_page(char *string, Address_Mode mode);
int check_external(char *string, Address_Mode mode);
int check_io(char *string);

int check_immediate(char *string, Immediate_Mode mode);
int check_big_immediate(char *string, Immediate_Mode mode);
int check_byte_immediate(char *string);

int check_if_label(char *string);
int check_if_label_colon(char *string);
int check_flags(char *string);

char* get_macro(char *string);
int get_label_address(char *string);
int get_cache_page_address(char *string);
int get_big_immediate_value(char *string);
Assembler_Arguments get_instruction(char *string);
