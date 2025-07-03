#include "parse.h"



int parse_instructions(){

    for(int c_line = 0; c_line < f.file_lines; c_line++){

        Assembler_Arguments tmp_instruction = get_instruction(f.file_arrays[c_line][TOKEN_ONE]);
        if(tmp_instruction == ERROR){

            printf("ERROR: failed to parse '%s' as an instruction in line '%d'\n", f.file_arrays[c_line][TOKEN_ONE], c_line + 1);
            return 1;

        } else{

            t.instruction_array[c_line] = tmp_instruction;

        }
    }
    return 0;
}

int parse_macros(){
    set.num_macros = 0;

    for(int c_line = 0; c_line < f.file_lines; c_line++){
        if(t.instruction_array[c_line] == SET_CONSTANT && t.num_tokens[c_line] == 3){
            set.num_macros++;
            set.macro = realloc(set.macro, sizeof(char*) * set.num_macros);
            set.macro_name = realloc(set.macro_name, sizeof(char*) * set.num_macros);
            set.macro[set.num_macros - 1] = malloc(sizeof(char) * f.file_array_size);
            set.macro_name[set.num_macros - 1] = malloc(sizeof(char) * f.file_array_size);

            strcpy(set.macro_name[set.num_macros - 1], f.file_arrays[c_line][TOKEN_TWO]);
            strcpy(set.macro[set.num_macros - 1], f.file_arrays[c_line][TOKEN_THREE]);

        } else if(t.instruction_array[c_line] == SET_CONSTANT && !(t.num_tokens[c_line] == 3)){
            printf("ERROR: %d arguments given for 'set' in line '%d', expected 3\n", t.num_tokens[c_line], c_line + 1);
            return 1;
        }
    }

    return 0;
}



int parse_labels(){
    l.num_labels = 0;

    for(int c_line = 0; c_line < f.file_lines; c_line++){
        if(t.instruction_array[c_line] == LABEL){
            if(l.num_labels > 0 && check_if_label(f.file_arrays[c_line][TOKEN_ONE])){
                printf("ERROR: label '%s' cannot repeat\n", f.file_arrays[c_line][TOKEN_ONE]);
                return 1;
            }
            l.num_labels++;
            l.label_strings = realloc(l.label_strings, sizeof(char*) * l.num_labels);
            l.label_strings[l.num_labels - 1] = malloc(sizeof(char) * f.file_array_size);
            l.label_addresses = realloc(l.label_addresses, sizeof(int) * l.num_labels);

            strcpy(l.label_strings[l.num_labels - 1], f.file_arrays[c_line][TOKEN_ONE]);
            l.label_addresses[l.num_labels - 1] = 0;
            
        }
    }

    return 0;
}



int parse_section_data(){
    int section_data = 0;
    for(int c_line = 0; c_line < f.file_lines; c_line++){
        if(t.instruction_array[c_line] == SECTION_DATA){
            section_data = 1;
            continue;
        } else if(t.instruction_array[c_line] == SECTION_TEXT){
            section_data = 0;
        }
        if(section_data == 0){
            continue;
        }

        int tmp = get_data_bytes(t.instruction_array[c_line], f.file_arrays[c_line], t.num_tokens[c_line], c_line, &t.opcode_array[c_line]);
        if(tmp == -1){
            printf("ERROR: incorrect syntax with line '%d' in .section_data, check syntax within macro definitions (aka 'set') -\n", c_line + 1);
            for(int i = 0; i < t.num_tokens[c_line]; i++){
                printf("%s ", f.file_arrays[c_line][i]);
            }
            printf("\n\n");
            return 1;
        }
        t.num_bytes[c_line] = tmp;
    }
    return 0;
}



int parse_section_text(){
    int section_text = 0;
    int section_data = 0;
    for(int c_line = 0; c_line < f.file_lines; c_line++){
        if(t.instruction_array[c_line] == SECTION_TEXT){
            section_text = 1;
            continue;
        } else if(t.instruction_array[c_line] == SECTION_DATA){
            section_text = 0;
            section_data = 1;
        }
        if(section_text == 0){
            continue;
        }

        int tmp = get_text_bytes(t.instruction_array[c_line], f.file_arrays[c_line], t.num_tokens[c_line], c_line, &t.opcode_array[c_line]);
        if(tmp == -1){
            printf("ERROR: incorrect syntax with line '%d' in .section_text, check syntax within macro definitions (aka 'set') -\n", c_line + 1);
            for(int i = 0; i < t.num_tokens[c_line]; i++){
                printf("%s ", f.file_arrays[c_line][i]);
            }
            printf("\n\n");
            return 1;
        }
        t.num_bytes[c_line] = tmp;
    }

    if(section_text == 0 && section_data == 0){
        printf("ERROR: No '.section_text' found\n");
        return 1;
    }

    return 0;
}



int parse_sizeof(){
    int enable_sizeof = 0;
    int enable_count = 0;
    for(int c_line = 0; c_line < f.file_lines; c_line++){
        if(t.instruction_array[c_line] == SIZEOF){
            enable_sizeof = 1;
        }
        if(enable_sizeof == 0){
            continue;
        }

        //LABEL sizeof
        if((t.num_tokens[c_line] == 2) && (strcmp(f.file_arrays[c_line][TOKEN_TWO], "LABELS") == 0)){
            printf("\nALL LABELS w/ addresses\n");
            for(int i = 0; i < l.num_labels; i++){
                printf("    %s - %d\n", l.label_strings[i], l.label_addresses[i]);
            }
            printf("\n");
            enable_sizeof = 0;
            enable_count = 0;
            continue;
        }

        //LINES sizeof
        if((t.num_tokens[c_line] == 2) && (strcmp(f.file_arrays[c_line][TOKEN_TWO], "LINES") == 0)){
            printf("\nALL LINES w/ size in bytes\n");
            for(int i = 0; i < f.file_lines; i++){
                printf("    %s - %d\n", f.file_arrays[i][0], t.num_bytes[i]);
            }
            printf("\n");
            enable_sizeof = 0;
            enable_count = 0;
            continue;
        }

        //previous line sizeof

        if((t.num_tokens[c_line] == 2) && (strcmp(f.file_arrays[c_line][TOKEN_TWO], "PREVIOUS") == 0)){
            if(c_line == 0){
                printf("ERROR: cannot use 'sizeof previous' in the first line of program\n");
                return 1;
            }
        }

        if((t.num_tokens[c_line] == 2) && (strcmp(f.file_arrays[c_line][TOKEN_TWO], "PREVIOUS") == 0)){
            for(int i = 0; i < t.num_tokens[c_line - 1]; i++){
                printf("%s ", f.file_arrays[c_line - 1][i]);
            }
            printf("- line '%d' size in bytes: %d\n", c_line, t.num_bytes[c_line - 1]);
            enable_sizeof = 0;
            enable_count = 0;
            continue;
        }
        
        if((t.num_tokens[c_line] == 2) && !(strcmp(f.file_arrays[c_line][TOKEN_TWO], "PREVIOUS") == 0)){
            printf("ERROR: expected second token at line '%d'\n", c_line + 1);
            return 1;
        }


        
        //label to label sizeof
        if((t.num_tokens[c_line] == 3) && (check_if_label_colon(f.file_arrays[c_line][TOKEN_TWO]) && check_if_label_colon(f.file_arrays[c_line][TOKEN_THREE]))){
            int sum = 0;
            char *start_label = f.file_arrays[c_line][TOKEN_TWO];
            char *end_label = f.file_arrays[c_line][TOKEN_THREE];
            char *current_token;
            for(int i = 0; i < f.file_lines; i++){
                current_token = strdup(f.file_arrays[i][TOKEN_ONE]);
                current_token[strcspn(current_token, ":")] = 0;

                if(strcmp(start_label, current_token) == 0){
                    enable_count = 1;
                }    
                if(strcmp(end_label, current_token) == 0){
                    enable_count = 0;
                }    
                if(enable_count == 0){
                    continue;
                }

                sum += t.num_bytes[i];
            }
            printf("'%s' to '%s' - size in bytes: %d\n", start_label, end_label, sum);
            enable_sizeof = 0;
            enable_count = 0;
            continue;
        }

        
        //big fat error checking :)
        if(t.num_tokens[c_line] < 2){
            printf("ERROR: at line '%d', minimum arguments for 'sizeof' is 2, was given %d\n", c_line + 1, t.num_tokens[c_line]);
            return 1;            
        }
        if((t.num_tokens[c_line] > 3)){
            printf("ERROR: at line '%d', maximum arguments for 'sizeof' is 3, was given %d\n", c_line + 1, t.num_tokens[c_line]);
            return 1;
        }
        if(strchr(f.file_arrays[c_line][TOKEN_TWO], ':')){
            printf("ERROR: at line '%d', '%s' cannot have a semicolon, just use name of label\n", c_line + 1, f.file_arrays[c_line][TOKEN_TWO]);
            return 1;
        }
        if(strchr(f.file_arrays[c_line][TOKEN_THREE], ':')){
            printf("ERROR: at line '%d', '%s' cannot have a semicolon, just use name of label\n", c_line + 1, f.file_arrays[c_line][TOKEN_THREE]);
            return 1;
        }
        if((t.num_tokens[c_line] == 3) && !(check_if_label_colon(f.file_arrays[c_line][TOKEN_TWO]))){
            printf("ERROR: at line '%d', '%s' is not defined as a label\n", c_line + 1, f.file_arrays[c_line][TOKEN_TWO]);
            return 1;
        }
        if((t.num_tokens[c_line] == 3) && !(check_if_label_colon(f.file_arrays[c_line][TOKEN_THREE]))){
            printf("ERROR: at line '%d', '%s' is not defined as a label\n", c_line + 1, f.file_arrays[c_line][TOKEN_THREE]);
            return 1;
        }
    }
    return 0;
}



//parce.c
int calculate_label_addresses(){

    for(int c_label = 0; c_label < l.num_labels; c_label++){

        int sum = 0;
        int disable_count = 0;
        for(int c_line = 0; c_line < f.file_lines; c_line++){

            if(disable_count == 1)
                continue;
            if(t.instruction_array[c_line] == AT_ADDRESS)
                sum = get_big_immediate_value(f.file_arrays[c_line][TOKEN_TWO]) + 1;
        
            sum += t.num_bytes[c_line];

            if(t.instruction_array[c_line] == LABEL && strcmp(l.label_strings[c_label], f.file_arrays[c_line][TOKEN_ONE]) == 0)
                disable_count = 1;    
        }
        sum--;
        if(sum < 0)
            sum = 0;
        l.label_addresses[c_label] = sum;
    }

    l.total_bytes = 0;
    for(int i = 0; i < f.file_lines; i++){
        l.total_bytes += t.num_bytes[i];
    }

    return 0;
}



//parce.c
int parse_big_label_addresses(){

    for(int c_line = 0; c_line < f.file_lines; c_line++){

        Assembler_Arguments instruction = t.instruction_array[c_line];
        Opcode_Type opcode = t.opcode_array[c_line];
        char *label;
        int address;
        switch(instruction){

            case(CALL):
                if(!(opcode == CAL_DIRECT)){
                    return 0;
                }
                label = f.file_arrays[c_line][TOKEN_TWO];
                address = get_label_address_colon(label);

                if(address + 1 > 255){
                    t.num_bytes[c_line] = 4;
                }
                if(address + 1 > 1023){
                    printf("ERROR: BYTE OVERFLOW at line '%d'", c_line);
                    return 1;
                }
                calculate_label_addresses();

                return 0;

            case(JUMP):
                if(!(opcode == JMP_DIRECT)){
                    return 0;
                }
                label = f.file_arrays[c_line][TOKEN_TWO];
                address = get_label_address_colon(label);

                if(address + 1 > 255){
                    t.num_bytes[c_line] = 4;
                }
                if(address + 1 > 1023){
                    printf("ERROR: BYTE OVERFLOW at line '%d'", c_line);
                    return 1;
                }
                calculate_label_addresses();

                return 0;

            case(CALL_IF):
                if(!(opcode == CIF_DIRECT)){
                    return 0;
                }
                label = f.file_arrays[c_line][TOKEN_THREE];
                address = get_label_address_colon(label);

                if(address + 1 > 255){
                    t.num_bytes[c_line] = 4;
                }
                if(address + 1 > 1023){
                    printf("ERROR: BYTE OVERFLOW at line '%d'", c_line);
                    return 1;
                }
                calculate_label_addresses();

                return 0;

            case(JUMP_IF):
                if(!(opcode == JIF_DIRECT)){
                    return 0;
                }
                label = f.file_arrays[c_line][TOKEN_THREE];
                address = get_label_address_colon(label);

                if(address + 1 > 255){
                    t.num_bytes[c_line] = 4;
                }
                if(address + 1 > 1023){
                    printf("ERROR: BYTE OVERFLOW at line '%d'", c_line);
                    return 1;
                }
                calculate_label_addresses();

                return 0;

            default:
                continue;
        }
    }
    return 0;
}





//parce.c
int parse(){
    t.num_bytes = malloc(sizeof(int) * f.file_lines);
    t.instruction_array = malloc(sizeof(Assembler_Arguments) * f.file_lines);
    t.opcode_array = malloc(sizeof(Opcode_Type) * f.file_lines);
    memset(t.num_bytes, 0, sizeof(int) * f.file_lines);
    memset(t.instruction_array, 0, sizeof(int) * f.file_lines);
    memset(t.opcode_array, NONE, sizeof(int) * f.file_lines);
    
    if(parse_instructions()){
        printf("ERROR: parse_instructions()\n");
        return 1;
    }

    if(parse_macros()){
        printf("ERROR: parse_macros()\n");
        return 1;
    }

    if(parse_labels()){
        printf("ERROR: parse_labels()\n");
        return 1;
    }

    if(parse_section_data()){
        printf("ERROR: parse_section_data()\n");
        return 1;
    }

    if(parse_section_text()){
        printf("ERROR: parse_section_text()\n");
        return 1;
    }

    if(calculate_label_addresses()){
        printf("ERROR: parse_label_addresses()\n");
        return 1;
    }

    if(parse_big_label_addresses()){
        printf("ERROR: parse_big_label_addresses()\n");
        return 1;
    }

    
    if(parse_sizeof()){
        printf("ERROR: parse_sizeof()\n");
        return 1;
    }
    
    return 0;
}