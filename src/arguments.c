#include "arguments.h"


/*

this file contains functions that are useful with arguments
in the program when assembling 

*/


//arguments.c, returns 1 when match, 0 when no match. EXAMPLE: 4_BYTES, 3_BYTES
int check_byte_immediate(char *string){

    regex_t byte_pattern;
    regcomp(&byte_pattern, "^([1-4])_bytes?$", REG_ICASE | REG_EXTENDED);
    int result;

    result = regexec(&byte_pattern, string, 0, NULL, 0);

    regfree(&byte_pattern);
    if(result == 0){
        return 1;
    }

    return 0;
}

//arguments.c, returns 1 when match, 0 when no match, checks for 10 bit immediate
int check_big_immediate(char *string, Immediate_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_immediate()\n");
        return -1;
    }

    int result;
    regex_t dec_pattern;
    regcomp(&dec_pattern, "^#(102[0-3]|10[0-1][0-9]|[1-9][0-9]{1,2}|[0-9])$", REG_ICASE | REG_EXTENDED);

    regex_t bin_pattern;
    regcomp(&bin_pattern, "^#0b[01]{1,10}$", REG_ICASE | REG_EXTENDED);

    regex_t hex_pattern;
    regcomp(&hex_pattern, "^#0x([0-3]?[0-9a-fA-F]{1,2})$", REG_ICASE | REG_EXTENDED);


    if(mode == DECIMAL_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&dec_pattern, string, 0, NULL, 0);

        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }

    if(mode == BINARY_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&bin_pattern, string, 0, NULL, 0);
   
        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }

    if(mode == HEXADECIMAL_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&hex_pattern, string, 0, NULL, 0);

        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }


    regfree(&hex_pattern);
    regfree(&dec_pattern);
    regfree(&bin_pattern);

    return 0;
}

//arguments.c, returns 1 when match, 0 when no match, checks for 8 bit immediates
int check_immediate(char *string, Immediate_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_immediate()\n");
        return -1;
    }

    int result;
    regex_t dec_pattern;
    regcomp(&dec_pattern, "^#(0|[1-9][0-9]?|1[0-9]{2}|2[0-4][0-9]|25[0-5])$", REG_ICASE | REG_EXTENDED);

    regex_t bin_pattern;
    regcomp(&bin_pattern, "^#0b[01]{1,8}$", REG_ICASE | REG_EXTENDED);

    regex_t hex_pattern;
    regcomp(&hex_pattern, "^#0x([0-9a-fA-F]{1,2})$", REG_ICASE | REG_EXTENDED);


    if(mode == DECIMAL_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&dec_pattern, string, 0, NULL, 0);

        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }

    if(mode == BINARY_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&bin_pattern, string, 0, NULL, 0);
   
        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }

    if(mode == HEXADECIMAL_IMMEDIATE || mode == ANY_IMMEDIATE){
        result = regexec(&hex_pattern, string, 0, NULL, 0);

        if(result == 0){
            regfree(&hex_pattern);
            regfree(&bin_pattern);
            regfree(&dec_pattern);
            return 1;
        }
    }

    if(string[0] == '+' && (mode == PAGE_ADDRESS || mode == ANY_IMMEDIATE)){
        char *dup_string = strdup(string);
        dup_string++;

        if(check_if_label_colon(dup_string)){
            return 1;
        }
    }

    if(string[0] == '&' && (mode == CACHE_ADDRESS || mode == ANY_IMMEDIATE)){
        char *dup_string = strdup(string);
        dup_string++;

        if(check_if_label_colon(dup_string)){
            return 1;
        }
    }

    if(string[0] == '=' && (mode == ANY_IMMEDIATE)){
        char *dup_string = strdup(string);
        dup_string++;

        if(check_if_label_colon(dup_string)){
            return 1;
        }
    }

    if(string[0] = '#' && isprint(string[1])){
        return 1;
    }

    regfree(&hex_pattern);
    regfree(&dec_pattern);
    regfree(&bin_pattern);

    return 0;
}

//arguments.c, returns 1 when match, 0 when no match
int check_cache(char *string, Address_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_cache()\n");
        return -1;
    }

    regex_t direct_pattern;
    regcomp(&direct_pattern, "^c(0|[1-9]|[1-5][0-9]|6[0-3])$", REG_ICASE | REG_EXTENDED);

    regex_t indirect_pattern;
    regcomp(&indirect_pattern, "^c\\[ptr\\]$", REG_ICASE | REG_EXTENDED);

    regex_t index_pattern;
    regcomp(&index_pattern, "^c\\{r[0-7]\\}$", REG_ICASE | REG_EXTENDED);    
    int result;
    //regexec() returns 0 if pattern matches

    if(mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&direct_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            regfree(&index_pattern);
            return 1;
        }
    }

    if(mode == INDIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&indirect_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            regfree(&index_pattern);
            return 1;
        }
    }

    if(mode == INDEX_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&index_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            regfree(&index_pattern);
            return 1;
        }
    }


    if(string[0] == '-' && (mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING)){
        char *dup_string = strdup(string);
        dup_string++;

        if(check_if_label_colon(dup_string)){
            return 1;
        }
    }


    regfree(&direct_pattern);
    regfree(&indirect_pattern);
    regfree(&index_pattern);

    return 0;
}



//arguments.c, returns 1 when match, 0 when no match
int check_reg(char *string, Address_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_register()\n");
        return -1;
    }
    if(mode == INDEX_ADDRESSING){
        printf("invalid Address_Mode given to check_register()\n");
        return -1;
    }

    regex_t direct_pattern;
    regcomp(&direct_pattern, "^r[0-7]$", REG_ICASE | REG_EXTENDED);

    regex_t indirect_pattern;
    regcomp(&indirect_pattern, "^r\\[ptr\\]$", REG_ICASE | REG_EXTENDED);

    
    int result;
    //regexec() returns 0 if pattern matches

    if(mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&direct_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    if(mode == INDIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&indirect_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    regfree(&direct_pattern);
    regfree(&indirect_pattern);


    return 0;
}



//arguments.c, returns 1 when match, 0 when no match
int check_reg_flags(char *string, Address_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_register()\n");
        return -1;
    }
    if(mode == INDEX_ADDRESSING){
        printf("invalid Address_Mode given to check_register()\n");
        return -1;
    }

    regex_t direct_pattern;
    regcomp(&direct_pattern, "^\\*r[0-7]$", REG_ICASE | REG_EXTENDED);

    regex_t indirect_pattern;
    regcomp(&indirect_pattern, "^\\*r\\[ptr\\]$", REG_ICASE | REG_EXTENDED);

    
    int result;
    //regexec() returns 0 if pattern matches

    if(mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&direct_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    if(mode == INDIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&indirect_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    regfree(&direct_pattern);
    regfree(&indirect_pattern);


    return 0;
}


//arguments.c
int check_io(char *string){
    if(string == NULL){
        printf("bad string given for 'check_io()\n");
        return -1;
    }    
    regex_t pattern;
    regcomp(&pattern, "^io[0-7]$", REG_ICASE | REG_EXTENDED);    
    int result = regexec(&pattern, string, 0, NULL, 0);
    regfree(&pattern);

    if(result == 0){
        return 1;
    } else{
        return 0;
    }
}



//arguments.c, returns 1 when match, 0 when no match
int check_page(char *string, Address_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_page()\n");
        return -1;
    }
    if(mode == INDEX_ADDRESSING){
        printf("invalid Address_Mode given to check_page()\n");
        return -1;
    }

    regex_t direct_pattern;
    regcomp(&direct_pattern, "^p(1[0-5]|[0-9])$", REG_ICASE | REG_EXTENDED);

    regex_t indirect_pattern;
    regcomp(&indirect_pattern, "^p\\[ptr\\]$", REG_ICASE | REG_EXTENDED);

    
    int result;
    //regexec() returns 0 if pattern matches

    if(mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&direct_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    if(mode == INDIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&indirect_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    if(string[0] == '+' && (mode == DIRECT_ADDRESSING || mode == ANY_IMMEDIATE)){
        char *dup_string = strdup(string);
        dup_string++;

        if(check_if_label_colon(dup_string)){
            return 1;
        }
    }

    regfree(&direct_pattern);
    regfree(&indirect_pattern);


    return 0;
}



//arguments.c, returns 1 when match, 0 when no match
int check_external(char *string, Address_Mode mode){

    if(string == NULL){
        printf("bad string given for 'check_external()\n");
        return -1;
    }
    if(mode == INDEX_ADDRESSING){
        printf("invalid Address_Mode given to check_external()\n");
        return -1;
    }

    regex_t direct_pattern;
    regcomp(&direct_pattern, "^x(0|[1-9][0-9]?|1[0-9]{2}|2[0-4][0-9]|25[0-5])$", REG_ICASE | REG_EXTENDED);

    regex_t indirect_pattern;
    regcomp(&indirect_pattern, "^x\\[ptr\\]$", REG_ICASE | REG_EXTENDED);

    
    int result;
    //regexec() returns 0 if pattern matches

    if(mode == DIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&direct_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    if(mode == INDIRECT_ADDRESSING || mode == ANY_ADDRESSING){
        result = regexec(&indirect_pattern, string, 0, NULL, 0);
        if(result == 0){
            regfree(&direct_pattern);
            regfree(&indirect_pattern);
            return 1;
        }
    }

    regfree(&direct_pattern);
    regfree(&indirect_pattern);


    return 0;
}



//argument.c, returns 1 if label exists, returns 0 if not
int check_if_label(char *string){
    
    for(int i = 0; i < l.num_labels; i++){
        if(strcmp(string, l.label_strings[i]) == 0){
            return 1;
        }
    }
    return 0;
}



//argument.c, returns 1 if label exists without the colon, returns 0 if not
int check_if_label_colon(char *string){
    
    
    for(int i = 0; i < l.num_labels; i++){
        const char *label_with_colon = l.label_strings[i];
        size_t length = strlen(l.label_strings[i]);
        if(length > 0 && label_with_colon[length - 1] == ':'){
            if(strncmp(string, label_with_colon, length - 1) == 0 && string[length - 1] == '\0'){
                return 1;
            }
        }
    }

    return 0;
}



//argument.c, returns 1 if label exists without the colon and with '+' or '-' or '&', returns 0 if not
int check_label_colon_cache_page(char *string){
    
    if(!(string[0] == '&' || string[0] == '-' || string[0] == '+' || string[0] == '=')){
        return 0;
    }
    char *dup_string = strdup(string);
    dup_string++;

    for(int i = 0; i < l.num_labels; i++){
        const char *label_with_colon = l.label_strings[i];
        size_t length = strlen(l.label_strings[i]);
        if(length > 0 && label_with_colon[length - 1] == ':'){
            if(strncmp(dup_string, label_with_colon, length - 1) == 0 && dup_string[length - 1] == '\0'){
                return 1;
            }
        }
    }

    return 0;
}



//arguments.c, returns 1 if string a flag
int check_flags(char *string){
    if(strcmp(string, "zero") == 0){
        return 1;
    }
    if(strcmp(string, "car") == 0){
        return 1;
    }
    if(strcmp(string, "over") == 0){
        return 1;
    }
    if(strcmp(string, "neg") == 0){
        return 1;
    }
    if(strcmp(string, "==") == 0){
        return 1;
    }
    if(strcmp(string, "!=") == 0){
        return 1;
    }
    if(strcmp(string, "<<") == 0){
        return 1;
    }
    if(strcmp(string, ">>") == 0){
        return 1;
    }
    if(strcmp(string, "<=") == 0){
        return 1;
    }
    if(strcmp(string, ">=") == 0){
        return 1;
    }
    if(strcmp(string, "S<<") == 0){
        return 1;
    }
    if(strcmp(string, "S>>") == 0){
        return 1;
    }
    if(strcmp(string, "S<=") == 0){
        return 1;
    }
    if(strcmp(string, "S>=") == 0){
        return 1;
    }
    return 0;
}



//arguments.c, returns string tied with a macro
char* get_macro(char *string){

    for(int i = 0; i < set.num_macros; i++){
        if(strcmp(string, set.macro_name[i]) == 0){
            return set.macro[i];
        }
    }
    return string;
}



//arguments.c, returns address tied to label
int get_label_address_colon(char *string){

    for(int i = 0; i < l.num_labels; i++){
        const char *label_with_colon = l.label_strings[i];
        size_t length = strlen(l.label_strings[i]);
        if(length > 0 && label_with_colon[length - 1] == ':'){
            if(strncmp(string, label_with_colon, length - 1) == 0 && string[length - 1] == '\0'){
                return l.label_addresses[i];
            }
        }
    }
    return -1;
}



//arguments.c, returns cache or page address depending if label starts with '&' or '+', returns -1 if error
int get_cache_page_address(char *string){
    //page address
    if(string[0] == '+'){
        char *dup_string = strdup(string);
        dup_string++;

        for(int i = 0; i < l.num_labels; i++){
            const char *label_with_colon = l.label_strings[i];
            size_t length = strlen(l.label_strings[i]);
            if(length > 0 && label_with_colon[length - 1] == ':'){
                if(strncmp(dup_string, label_with_colon, length - 1) == 0 && dup_string[length - 1] == '\0'){
                    int page_addr = l.label_addresses[i];
                    return page_addr >>= 6;
                }
            }            
        }
    }

    if(string[0] == '&' || string[0] == '-'){
        char *dup_string = strdup(string);
        dup_string++;

        for(int i = 0; i < l.num_labels; i++){
            const char *label_with_colon = l.label_strings[i];
            size_t length = strlen(l.label_strings[i]);
            if(length > 0 && label_with_colon[length - 1] == ':'){
                if(strncmp(dup_string, label_with_colon, length - 1) == 0 && dup_string[length - 1] == '\0'){
                    int page_addr = l.label_addresses[i];
                    int cache_addr = page_addr;
                    page_addr >>= 6;
                    cache_addr -= (page_addr << 6); 
                    return cache_addr;                    
                }
            }            
        }
    }

    if(string[0] == '='){
        char *dup_string = strdup(string);
        dup_string++;

        for(int i = 0; i < l.num_labels; i++){
            const char *label_with_colon = l.label_strings[i];
            size_t length = strlen(l.label_strings[i]);
            if(length > 0 && label_with_colon[length - 1] == ':'){
                if(strncmp(dup_string, label_with_colon, length - 1) == 0 && dup_string[length - 1] == '\0'){
                    int upper_two = l.label_addresses[i];
                    int bottom_eight = upper_two;
                    upper_two >>= 8;
                    bottom_eight -= (upper_two << 8); 
                    return bottom_eight;                    
                }
            }            
        }        
    }

    return -1;
}



//arguments.c, returns char* for arrays of binary, returns NULL if error, must free output char*
char* integer_binary_converter(int integer){

    if(integer < 0){
        return NULL;
    }
    if(integer < 256){
        char *binary_string = malloc(sizeof(char) * 9);
        memset(binary_string, '0', sizeof(char) * 9);

        for(int i = 7; integer > 0; i--){
            binary_string[i] = integer % 2 + '0';
            integer /= 2;
        }

        binary_string[8] = '\0';
        return binary_string;
    }
    if(integer < 1024){
        char *binary_string = malloc(sizeof(char) * 11);
        memset(binary_string, '0', sizeof(char) * 11);

        for(int i = 9; integer > 0; i--){
            binary_string[i] = integer % 2 + '0';
            integer /= 2;
        }

        binary_string[10] = '\0';
        return binary_string;
    }

    if(integer > 1023){
        return NULL;
    }
}



//arguments.c, returns immediate value, returns -1 if error
int get_big_immediate_value(char *string){
    int label_immediate = get_cache_page_address(string);
    if(!(label_immediate == -1)){
        return label_immediate;
    }


    if(check_big_immediate(string, DECIMAL_IMMEDIATE)){
        char *dup = strdup(string);
        dup += 1;
        return strtol(dup, NULL, 10);
    }
    if(check_big_immediate(string, BINARY_IMMEDIATE)){
        char *dup = strdup(string);
        dup += 3;
        return strtol(dup, NULL, 2);
    }
    if(check_big_immediate(string, HEXADECIMAL_IMMEDIATE)){
        char *dup = strdup(string);
        dup += 3;
        return strtol(dup, NULL, 16);
    }

    if(string[0] = '#' && isprint(string[1])){
        return string[1];
    }

    return -1;
}



//arguments.c, returns value of an arguments, aka r0 would return 0
int get_argument_value(char *string){


    if(check_label_colon_cache_page(string)){
        return get_cache_page_address(string);
    }

    if(check_if_label_colon(string)){
        return get_label_address_colon(string);
    }

    if(check_reg(string, ANY_ADDRESSING)){
        if(check_reg(string, DIRECT_ADDRESSING)){
            return strtol(string + 1, NULL, 10);
        }
        if(check_reg(string, INDIRECT_ADDRESSING)){
            return 0;
        }
    }


    if(check_reg_flags(string, ANY_ADDRESSING)){
        if(check_reg_flags(string, DIRECT_ADDRESSING)){
            return string[2] - '0';
        }
        if(check_reg_flags(string, INDIRECT_ADDRESSING)){
            return 0;
        }        
    }


    if(check_cache(string, ANY_ADDRESSING)){
        if(check_cache(string, DIRECT_ADDRESSING)){
            return strtol(string + 1, NULL, 10);
        }
        if(check_cache(string, INDIRECT_ADDRESSING)){
            return 0;
        }
        if(check_cache(string, INDEX_ADDRESSING)){
            return string[3] - '0';
        }
    }

    if(check_page(string, ANY_ADDRESSING)){
        if(check_page(string, DIRECT_ADDRESSING)){
            return strtol(string + 1, NULL, 10);
        }
        if(check_page(string, INDIRECT_ADDRESSING)){
            return 0;
        }
    }

    if(check_external(string, ANY_ADDRESSING)){
        if(check_external(string, DIRECT_ADDRESSING)){
            return strtol(string + 1, NULL, 10);
        }
        if(check_external(string, INDIRECT_ADDRESSING)){
            return 0;
        }
    }

    if(check_io(string)){
        return string[2] - '0';
    }


    return -1;
}



//arguments.c, returns ENUM for instruction type, returns ERROR if no match
Assembler_Arguments get_instruction(char *string){
    if(strcasecmp("add", string) == 0)
        return ALU_OP;
    if(strcasecmp("sub", string) == 0)
        return ALU_OP;
    if(strcasecmp("lls", string) == 0)
        return ALU_OP;
    if(strcasecmp("lrs", string) == 0)
        return ALU_OP;
    if(strcasecmp("ars", string) == 0)
        return ALU_OP;
    if(strcasecmp("or", string) == 0)
        return ALU_OP;
    if(strcasecmp("and", string) == 0)
        return ALU_OP;
    if(strcasecmp("xor", string) == 0)
        return ALU_OP;
    if(strcasecmp("nor", string) == 0)
        return ALU_OP;
    if(strcasecmp("nand", string) == 0)
        return ALU_OP;
    if(strcasecmp("xnor", string) == 0)
        return ALU_OP;
    if(strcasecmp("not", string) == 0)
        return ALU_OP;
    if(strcasecmp("cmp", string) == 0)
        return ALU_OP;
    if(strcasecmp("mov", string) == 0)
        return MOVE;
    if(strcasecmp("psh", string) == 0)
        return PUSH;
    if(strcasecmp("pop", string) == 0)
        return POP;
    if(strcasecmp("snd", string) == 0)
        return SEND;
    if(strcasecmp("rec", string) == 0)
        return RECEIVE;
    if(strcasecmp("wre", string) == 0)
        return WAIT_RECEIVE;
    if(strcasecmp("cld", string) == 0)
        return CACHE_LOAD;
    if(strcasecmp("cst", string) == 0)
        return CACHE_STORE;
    if(strcasecmp("xld", string) == 0)
        return EXTERNAL_LOAD;
    if(strcasecmp("xst", string) == 0)
        return EXTERNAL_STORE;
    if(strcasecmp("jmp", string) == 0)
        return JUMP;
    if(strcasecmp("jif", string) == 0)
        return JUMP_IF;
    if(strcasecmp("cal", string) == 0)
        return CALL;
    if(strcasecmp("cif", string) == 0)
        return CALL_IF;
    if(strcasecmp("ret", string) == 0)
        return RETURN;
    if(strcasecmp("nop", string) == 0)
        return NO_OP;
    if(strcasecmp("hlt", string) == 0)
        return HALT;
    if(strcasecmp("set", string) == 0)
        return SET_CONSTANT;
    if(strcasecmp("at", string) == 0)
        return AT_ADDRESS;
    if(strcasecmp(".section_data", string) == 0)
        return SECTION_DATA;
    if(strcasecmp(".section_text", string) == 0)
        return SECTION_TEXT;
    if(strcasecmp("sizeof", string) == 0)
        return SIZEOF;

    regex_t pattern;
    regcomp(&pattern, "^(\\w*):$", REG_ICASE | REG_EXTENDED);

    if(regexec(&pattern, string, 0, NULL, 0) == 0)
        return LABEL;

    regfree(&pattern);



    return ERROR;
}



// arguments.c
int get_alu_opcode(char *string){
    if(strcasecmp("add", string) == 0)
        return 0;
    if(strcasecmp("sub", string) == 0)
        return 1;
    if(strcasecmp("lls", string) == 0)
        return 2;
    if(strcasecmp("lrs", string) == 0)
        return 3;
    if(strcasecmp("ars", string) == 0)
        return 4;
    if(strcasecmp("or", string) == 0)
        return 8;
    if(strcasecmp("and", string) == 0)
        return 9;
    if(strcasecmp("xor", string) == 0)
        return 10;
    if(strcasecmp("nor", string) == 0)
        return 5;
    if(strcasecmp("nand", string) == 0)
        return 6;
    if(strcasecmp("xnor", string) == 0)
        return 7;
    if(strcasecmp("not", string) == 0)
        return 5;
    if(strcasecmp("cmp", string) == 0)
        return 1;    
}