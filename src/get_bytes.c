#include "get_bytes.h"

/*

    this part was by far the most annoying
    dear god

*/



// get_bytes.c
int check_alu_special(char *string){
    if(strcasecmp(string, "not") == 0){
        return 1;
    }
    if(strcasecmp(string, "ars") == 0){
        return 1;
    }
    if(strcasecmp(string, "llr") == 0){
        return 1;
    }
    if(strcasecmp(string, "lls") == 0){
        return 1;
    }
    if(strcasecmp(string, "cmp") == 0){
        return 1;
    }
    return 0;
}



// get_bytes.c, returns bytes for line in .section_data
int get_data_bytes(Assembler_Arguments instruction, char **p_string, int MAX_TOKENS, int c_line, Opcode_Type *opcode){
    switch(instruction){

        case(SECTION_DATA):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                return 0;
            }
            return -1;

        case(AT_ADDRESS):
            if(MAX_TOKENS == 2 && check_big_immediate(p_string[TOKEN_TWO], ANY_IMMEDIATE)){
                *opcode = NONE;
                return 0;
            }
            return -1;

        case(SET_CONSTANT):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                return 0;
            }
            return -1;

        case(GENERATE_BIN):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                f.output_binary = 1;
                return 0;
            }

        case(GENERATE_HEX):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                f.output_binary = 0;
                return 0;
            }

        case(LABEL):
            
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                return 0;
            }

            if(MAX_TOKENS == 3){

                if(strcmp(".ascii", p_string[TOKEN_TWO]) == 0){
                    regex_t pattern;
                    regcomp(&pattern, "^\"([[:alnum:][:punct:]]*)\"$", REG_ICASE | REG_EXTENDED);
                    if(regexec(&pattern, p_string[TOKEN_THREE], 0, NULL, 0) != 0){
                        regfree(&pattern);
                        return -1;
                    }
                    regfree(&pattern);
                    *opcode = LABEL_STRING;
                    return strlen(p_string[TOKEN_THREE]) - 2;
                }
                if(strcmp(".byte", p_string[TOKEN_TWO]) == 0 && check_immediate(p_string[TOKEN_THREE], ANY_IMMEDIATE)){
                    *opcode = LABEL_INT;
                    return 1;
                }
                if((strcmp(".byte", p_string[TOKEN_TWO]) == 0 && !(check_immediate(p_string[TOKEN_THREE], ANY_IMMEDIATE)))){
                    printf("ERROR: '%s' at line '%d' is an invalid immediate\n",p_string[TOKEN_THREE], c_line );
                    return -1;
                }
            }
            
            return -1;  


            
        case(SIZEOF):
            if(MAX_TOKENS == 2){
                *opcode = NONE;
                return 0;                
            }
            if(MAX_TOKENS == 3){
                *opcode = NONE;
                return 0;                
            }
            
        default:
            return -1;
    }
    return -1;
}





//get_bytes.c, returns bytes for line in .section_text
int get_text_bytes(Assembler_Arguments instruction, char **p_string, int MAX_TOKENS, int c_line, Opcode_Type *opcode){

    switch(instruction){

        case(SET_CONSTANT):
            if(MAX_TOKENS == 3){
                *opcode = NONE;            
                return 0;                
            }
            return -1;

        case(SIZEOF):
            if(MAX_TOKENS == 2){
                *opcode = NONE;
                return 0;                
            }
            if(MAX_TOKENS == 3){
                *opcode = NONE;
                return 0;                
            }
            return -1;

        case(SECTION_TEXT):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                return 0;                
            }
            return -1;

        case(AT_ADDRESS):
            if(MAX_TOKENS == 2 && check_big_immediate(p_string[TOKEN_TWO], ANY_IMMEDIATE)){
                *opcode = NONE;
                return 0;                
            }
            return -1;

        case(LABEL):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                return 0;                
            }
            return -1;

        case(GENERATE_BIN):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                f.output_binary = 1;
                return 0;
            }

        case(GENERATE_HEX):
            if(MAX_TOKENS == 1){
                *opcode = NONE;
                f.output_binary = 0;
                return 0;
            }

        case(HALT):
            if(MAX_TOKENS == 2 && check_byte_immediate(p_string[TOKEN_TWO])){
                *opcode = HLT_DIRECT;
                return p_string[TOKEN_TWO][0] - '0';             
            }
            if(MAX_TOKENS == 1){
                *opcode = HLT_DIRECT;
                return 1;                
            }
            return -1;

        case(NO_OP):
            if(MAX_TOKENS == 2 && check_byte_immediate(p_string[TOKEN_TWO])){
                *opcode = NOP_DIRECT;
                return p_string[TOKEN_TWO][0] - '0';             
            }
            if(MAX_TOKENS == 1){
                *opcode = NOP_DIRECT;
                return 1;                
            }
            return -1;

        case(ALU_OP):

            //byte immediates (aka 4_bytes)          
            if(MAX_TOKENS == 5 && check_byte_immediate(p_string[TOKEN_FIVE])){
                if(check_alu_special(p_string[0])){
                    return -1;
                }
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                char *tk_4 = get_macro(p_string[TOKEN_FOUR]);
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_reg(tk_4, DIRECT_ADDRESSING)){
                    *opcode = ALU_2;
                    return p_string[TOKEN_FIVE][0] - '0';
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_reg(tk_4, DIRECT_ADDRESSING)){
                    *opcode = ALU_2;
                    return p_string[TOKEN_FIVE][0] - '0';
                }
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_immediate(tk_4, ANY_IMMEDIATE)){
                    *opcode = ALU_2_IMMEDIATE;
                    return p_string[TOKEN_FIVE][0] - '0';
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_immediate(tk_4, ANY_IMMEDIATE)){
                    *opcode = ALU_2_IMMEDIATE;
                    return p_string[TOKEN_FIVE][0] - '0';
                }
            }
            
            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                if(!(check_alu_special(p_string[0]))){
                    return -1;
                }
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                    *opcode = ALU_1;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                    *opcode = ALU_1;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){
                    *opcode = ALU_1_IMMEDIATE;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){
                    *opcode = ALU_1_IMMEDIATE;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
            }
            //normal bytes 
            if(MAX_TOKENS == 4){
                if(check_alu_special(p_string[0])){
                    return -1;
                }
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                char *tk_4 = get_macro(p_string[TOKEN_FOUR]);
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_reg(tk_4, DIRECT_ADDRESSING)){
                    *opcode = ALU_2;
                    return 3;
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_reg(tk_4, DIRECT_ADDRESSING)){
                    *opcode = ALU_2;
                    return 3;
                }
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_immediate(tk_4, ANY_IMMEDIATE)){
                    *opcode = ALU_2_IMMEDIATE;
                    return 4;
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING) && check_immediate(tk_4, ANY_IMMEDIATE)){
                    *opcode = ALU_2_IMMEDIATE;
                    return 4;
                }
            }
            
            if(MAX_TOKENS == 3){
                if(!(check_alu_special(p_string[0]))){
                    return -1;
                }
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                    *opcode = ALU_1;
                    return 3;
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                    *opcode = ALU_1;
                    return 3;
                }
                if(check_reg(tk_2, DIRECT_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){
                    *opcode = ALU_1_IMMEDIATE;
                    return 4;
                }
                if(check_reg_flags(tk_2, DIRECT_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){
                    *opcode = ALU_1_IMMEDIATE;
                    return 4;
                }
            }
            return -1;

        case(MOVE):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){

                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);

                //LDI
                if(check_reg(tk_2, ANY_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){

                    if(check_reg(tk_2, DIRECT_ADDRESSING)){
                        *opcode = LDI_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                        *opcode = LDI_INDIRECT_3;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
                //CTC
                if(check_cache(tk_2, ANY_ADDRESSING) && check_cache(tk_3, ANY_ADDRESSING)){

                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTC_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTC_INDIRECT_3;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = CTC_INDIRECT_2;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
                //RTR
                if(check_reg(tk_2, ANY_ADDRESSING) && check_reg(tk_3, ANY_ADDRESSING)){
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTR_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTR_INDIRECT_3;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTR_INDIRECT_2;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
                //RTP
                if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, ANY_ADDRESSING)){
                    if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTP_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTP_INDIRECT_2;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
                //CTR
                if(check_reg(tk_2, ANY_ADDRESSING) && check_cache(tk_3, ANY_ADDRESSING)){
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTR_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTR_INDIRECT_3;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = CTR_INDIRECT_2;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDEX_ADDRESSING)){
                        *opcode = CTR_INDEX;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
                //RTC
                if(check_cache(tk_2, ANY_ADDRESSING) && check_reg(tk_3, ANY_ADDRESSING)){
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_DIRECT;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_INDIRECT_3;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTC_INDIRECT_2;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                    if(check_cache(tk_2, INDEX_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_INDEX;
                        return p_string[TOKEN_FOUR][0] - '0';
                    }
                }
            }

            if(MAX_TOKENS == 3){

                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                


                //LDI
                if(check_reg(tk_2, ANY_ADDRESSING) && check_immediate(tk_3, ANY_IMMEDIATE)){

                    if(check_reg(tk_2, DIRECT_ADDRESSING)){
                        *opcode = LDI_DIRECT;
                        return 4;
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                        *opcode = LDI_INDIRECT_3;
                        return 4;
                    }
                }

                //CTC
                if(check_cache(tk_2, ANY_ADDRESSING) && check_cache(tk_3, ANY_ADDRESSING)){

                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTC_DIRECT;
                        return 3;
                    }
                    if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTC_INDIRECT_3;
                        return 2;
                    }
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = CTC_INDIRECT_2;
                        return 3;
                    }
                }
                //RTR
                if(check_reg(tk_2, ANY_ADDRESSING) && check_reg(tk_3, ANY_ADDRESSING)){
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTR_DIRECT;
                        return 3;
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTR_INDIRECT_3;
                        return 2;
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTR_INDIRECT_2;
                        return 3;
                    }
                }
                //RTP
                if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, ANY_ADDRESSING)){
                    if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTP_DIRECT;
                        return 2;
                    }
                    if((strcasecmp("ptr", tk_2) == 0) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTP_INDIRECT_2;
                        return 1;
                    }
                }
                //CTR
                if(check_reg(tk_2, ANY_ADDRESSING) && check_cache(tk_3, ANY_ADDRESSING)){
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTR_DIRECT;
                        return 3;
                    }
                    if(check_reg(tk_2, INDIRECT_ADDRESSING) && check_cache(tk_3, DIRECT_ADDRESSING)){
                        *opcode = CTR_INDIRECT_3;
                        return 2;
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = CTR_INDIRECT_2;
                        return 3;
                    }
                    if(check_reg(tk_2, DIRECT_ADDRESSING) && check_cache(tk_3, INDEX_ADDRESSING)){
                        *opcode = CTR_INDEX;
                        return 3;
                    }
                }
                //RTC
                if(check_cache(tk_2, ANY_ADDRESSING) && check_reg(tk_3, ANY_ADDRESSING)){
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_DIRECT;
                        return 3;
                    }
                    if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_INDIRECT_3;
                        return 2;
                    }
                    if(check_cache(tk_2, DIRECT_ADDRESSING) && check_reg(tk_3, INDIRECT_ADDRESSING)){
                        *opcode = RTC_INDIRECT_2;
                        return 3;
                    }
                    if(check_cache(tk_2, INDEX_ADDRESSING) && check_reg(tk_3, DIRECT_ADDRESSING)){
                        *opcode = RTC_INDEX;
                        return 2;
                    }
                }
            }
            return -1;

        case(PUSH):

            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                
                if(check_reg(tk_2, DIRECT_ADDRESSING)){
                    *opcode = PSH_DIRECT;
                    return p_string[TOKEN_THREE][0] - '0';
                }
                if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = PSH_INDIRECT_2;
                    return p_string[TOKEN_THREE][0] - '0';
                }                
            }
            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);

                if(check_reg(tk_2, DIRECT_ADDRESSING)){
                    *opcode = PSH_DIRECT;
                    return 2;
                }
                if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = PSH_INDIRECT_2;
                    return 1;
                }
            }
            return -1;

        case(POP):

            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                
                if(check_reg(tk_2, DIRECT_ADDRESSING)){
                    *opcode = POP_DIRECT;
                    return p_string[TOKEN_THREE][0] - '0';
                }
                if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = POP_INDIRECT_3;
                    return p_string[TOKEN_THREE][0] - '0';
                }                
            }
            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);

                if(check_reg(tk_2, DIRECT_ADDRESSING)){
                    *opcode = POP_DIRECT;
                    return 3;
                }
                if(check_reg(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = POP_INDIRECT_3;
                    return 1;
                }
            }
            return -1;

        case(CACHE_LOAD):
            
            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_page(tk_2, DIRECT_ADDRESSING)){
                    *opcode = CLD_DIRECT;   
                    return p_string[TOKEN_THREE][0] - '0';
                }

                if(check_page(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = CLD_INDIRECT_2;    
                    return p_string[TOKEN_THREE][0] - '0';
                }
            }

            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_page(tk_2, DIRECT_ADDRESSING)){
                    *opcode = CLD_DIRECT;   
                    return 2; 
                }

                if(check_page(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = CLD_INDIRECT_2;    
                    return 1;
                }
            }
            return -1;

        case(CACHE_STORE):
            

            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_page(tk_2, DIRECT_ADDRESSING)){
                    *opcode = CST_DIRECT;   
                    return p_string[TOKEN_THREE][0] - '0';
                }

                if(check_page(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = CST_INDIRECT_2;    
                    return p_string[TOKEN_THREE][0] - '0';
                }
            }

            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_page(tk_2, DIRECT_ADDRESSING)){
                    *opcode = CST_DIRECT;   
                    return 2; 
                }

                if(check_page(tk_2, INDIRECT_ADDRESSING)){
                    *opcode = CST_INDIRECT_2;    
                    return 1;
                }
            }
            return -1;

        case(EXTERNAL_LOAD):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);                
                if(check_page(tk_2, DIRECT_ADDRESSING) && check_external(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XLD_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_page(tk_2, INDIRECT_ADDRESSING) && check_external(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XLD_INDIRECT_2;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_page(tk_2, DIRECT_ADDRESSING) && check_external(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = XLD_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
            }

            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_page(tk_2, DIRECT_ADDRESSING) && check_external(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XLD_DIRECT;
                    return 3;
                }
                if(check_page(tk_2, INDIRECT_ADDRESSING) && check_external(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XLD_INDIRECT_2;
                    return 3;
                }
                if(check_page(tk_2, DIRECT_ADDRESSING) && check_external(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = XLD_INDIRECT_3;
                    return 2;
                }
            }
            return -1;

        case(EXTERNAL_STORE):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_external(tk_2, DIRECT_ADDRESSING) && check_page(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XST_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_external(tk_2, INDIRECT_ADDRESSING) && check_page(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XST_INDIRECT_2;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_external(tk_2, DIRECT_ADDRESSING) && check_page(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = XST_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
            }

            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_external(tk_2, DIRECT_ADDRESSING) && check_page(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XST_DIRECT;
                    return 3;
                }
                if(check_external(tk_2, INDIRECT_ADDRESSING) && check_page(tk_3, DIRECT_ADDRESSING)){
                    *opcode = XST_INDIRECT_2;
                    return 2;
                }
                if(check_external(tk_2, DIRECT_ADDRESSING) && check_page(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = XST_INDIRECT_3;
                    return 3;
                }
            }
            return -1;

        case(SEND):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]); 
                if(check_io(tk_2) && check_cache(tk_3, DIRECT_ADDRESSING)){
                    *opcode = SND_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_io(tk_2) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = SND_INDIRECT_2;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_io(tk_2) && check_cache(tk_3, INDEX_ADDRESSING)){
                    *opcode = SND_INDEX;
                    return p_string[TOKEN_FOUR][0] - '0';
                }  
            }

            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_io(tk_2) && check_cache(tk_3, DIRECT_ADDRESSING)){
                    *opcode = SND_DIRECT;
                    return 4;
                }
                if(check_io(tk_2) && check_cache(tk_3, INDIRECT_ADDRESSING)){
                    *opcode = SND_INDIRECT_2;
                    return 4;
                }
                if(check_io(tk_2) && check_cache(tk_3, INDEX_ADDRESSING)){
                    *opcode = SND_INDEX;
                    return 4;
                }
            }
            return -1;

        case(WAIT_RECEIVE):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_cache(tk_2, DIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_cache(tk_2, INDEX_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_INDEX;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
            }

            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_cache(tk_2, DIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_DIRECT;
                    return 4;
                }
                if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_INDIRECT_3;
                    return 4;
                }
                if(check_cache(tk_2, INDEX_ADDRESSING) && check_io(tk_3)){
                    *opcode = WRE_INDEX;
                    return 4;
                }
            }
            return -1;

        case(RECEIVE):

            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_cache(tk_2, DIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
                if(check_cache(tk_2, INDEX_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_INDEX;
                    return p_string[TOKEN_FOUR][0] - '0';
                }
            }

            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);   
                if(check_cache(tk_2, DIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_DIRECT;
                    return 4;
                }
                if(check_cache(tk_2, INDIRECT_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_INDIRECT_3;
                    return 4;
                }
                if(check_cache(tk_2, INDEX_ADDRESSING) && check_io(tk_3)){
                    *opcode = REC_INDEX;
                    return 4;
                }
            }
            return -1;

        case(JUMP):
            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_if_label_colon(tk_2)){
                    *opcode = JMP_DIRECT;
                    return p_string[TOKEN_THREE][0] - '0';
                }   
                if(strcmp(tk_2, "ptr") == 0){
                    *opcode = JMP_INDIRECT_3;
                    return p_string[TOKEN_THREE][0] - '0';
                }                        
            }
            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_if_label_colon(tk_2)){
                    *opcode = JMP_DIRECT;
                    return 3;
                }   
                if(strcmp(tk_2, "ptr") == 0){
                    *opcode = JMP_INDIRECT_3;
                    return 1;
                }             
            }
            return -1;

        case(JUMP_IF):
            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_flags(tk_2) && check_if_label_colon(tk_3)){
                    *opcode = JIF_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }   
                if(check_flags(tk_2) && strcmp(tk_2, "ptr") == 0){
                    *opcode = JIF_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }      
                if(strcmp(tk_2, "ptr") == 0 && check_if_label_colon(tk_3)){
                    *opcode = JIF_INDIRECT_2;
                    return p_string[TOKEN_FOUR][0] - '0';
                }                   
            }
            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_flags(tk_2) && check_if_label_colon(tk_3)){
                    *opcode = JIF_DIRECT;
                    return 3;
                }   
                if(check_flags(tk_2) && strcmp(tk_2, "ptr") == 0){
                    *opcode = JIF_INDIRECT_3;
                    return 2;
                }      
                if(strcmp(tk_2, "ptr") == 0 && check_if_label_colon(tk_3)){
                    *opcode = JIF_INDIRECT_2;
                    return 3;
                }          
            }
            return -1;

        case(CALL):
            if(MAX_TOKENS == 3 && check_byte_immediate(p_string[TOKEN_THREE])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_if_label_colon(tk_2)){
                    *opcode = CAL_DIRECT;
                    return p_string[TOKEN_THREE][0] - '0';
                }   
                if(strcmp(tk_2, "ptr") == 0){
                    *opcode = CAL_INDIRECT_3;
                    return p_string[TOKEN_THREE][0] - '0';
                }                        
            }
            if(MAX_TOKENS == 2){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                if(check_if_label_colon(tk_2)){
                    *opcode = CAL_DIRECT;
                    return 3;
                }   
                if(strcmp(tk_2, "ptr") == 0){
                    *opcode = CAL_INDIRECT_3;
                    return 1;
                }             
            }
            return -1;

        case(CALL_IF):
            if(MAX_TOKENS == 4 && check_byte_immediate(p_string[TOKEN_FOUR])){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_flags(tk_2) && check_if_label_colon(tk_3)){
                    *opcode = CIF_DIRECT;
                    return p_string[TOKEN_FOUR][0] - '0';
                }   
                if(check_flags(tk_2) && strcmp(tk_2, "ptr") == 0){
                    *opcode = CIF_INDIRECT_3;
                    return p_string[TOKEN_FOUR][0] - '0';
                }      
                if(strcmp(tk_2, "ptr") == 0 && check_if_label_colon(tk_3)){
                    *opcode = CIF_INDIRECT_2;
                    return p_string[TOKEN_FOUR][0] - '0';
                }                   
            }
            if(MAX_TOKENS == 3){
                char *tk_2 = get_macro(p_string[TOKEN_TWO]);
                char *tk_3 = get_macro(p_string[TOKEN_THREE]);
                if(check_flags(tk_2) && check_if_label_colon(tk_3)){
                    *opcode = CIF_DIRECT;
                    return 3;
                }   
                if(check_flags(tk_2) && strcmp(tk_2, "ptr") == 0){
                    *opcode = CIF_INDIRECT_3;
                    return 2;
                }      
                if(strcmp(tk_2, "ptr") == 0 && check_if_label_colon(tk_3)){
                    *opcode = CIF_INDIRECT_2;
                    return 3;
                }          
            }
            return -1;

        case(RETURN):
            if(MAX_TOKENS == 1){
                return 1;
            }
            return -1;


        default:
            return -1;

    }
    return -1;
}
