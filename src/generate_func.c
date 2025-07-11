#include "generate_func.h"

char *tmp;

char* strint(int num){
    return integer_binary_converter(num);
}



char* generate_opcode(int num_bytes, int opcode){
    num_bytes -= 1;
    opcode += (num_bytes <<= 6);
    return strint(opcode);
}

// AOP functions

int generate_alu_2(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4){
    
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;
    }
    if(c_bytes >= 2){
        int reg_a = get_argument_value(tk_3);
        int reg_b = get_argument_value(tk_4);
        reg_a += (reg_b <<= 3);
        tmp = strint(reg_a);
        f.output_arrays[total_bytes + 1] = tmp;
    }
    if(c_bytes >= 3){
        int reg_write = get_argument_value(tk_2);
        int alu_op = get_alu_opcode(p_string[0]);
        int flag = check_reg_flags(tk_2, ANY_ADDRESSING);
        alu_op <<= 3;
        flag <<= 7;
        reg_write += (alu_op + flag);
        tmp = strint(reg_write);
        f.output_arrays[total_bytes + 2] = tmp;
    }    
    return 0;
} 

int generate_alu_2_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3, char *tk_4){
    
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;
    }
    if(c_bytes >= 2){
        int reg_a = get_argument_value(tk_3);
        tmp = strint(reg_a);
        f.output_arrays[total_bytes + 1] = tmp;
    }
    if(c_bytes >= 3){
        int reg_write = get_argument_value(tk_2);
        int alu_op = get_alu_opcode(p_string[0]);
        int flag = check_reg_flags(tk_2, ANY_ADDRESSING);
        alu_op <<= 3;
        flag <<= 7;
        reg_write += (alu_op + flag);
        tmp = strint(reg_write);
        f.output_arrays[total_bytes + 2] = tmp;
    }    
    if(c_bytes == 4){
        f.output_arrays[total_bytes + 3] = strint(get_big_immediate_value(tk_4));
    }

    return 0;
} 

int generate_alu_1(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3){
    
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;
    }
    if(c_bytes >= 2){
        if(strcasecmp(p_string[0], "cmp") == 0){
            int reg_a = get_argument_value(tk_2);
            int reg_b = get_argument_value(tk_3);
            reg_a += (reg_b <<= 3);
            reg_a += 128;
            tmp = strint(reg_a);
            f.output_arrays[total_bytes + 1] = tmp;
        } else{
            int reg_a = get_argument_value(tk_3);
            reg_a += (reg_a <<= 3);
            tmp = strint(reg_a);
            f.output_arrays[total_bytes + 1] = tmp;
        }
    }
    if(c_bytes >= 3){
        if(strcasecmp(p_string[0], "cmp") == 0){
            int alu_op = get_alu_opcode(p_string[0]);
            alu_op <<= 3;
            tmp = strint(alu_op);
            f.output_arrays[total_bytes + 2] = tmp;
        } else{
            int reg_write = get_argument_value(tk_2);
            int alu_op = get_alu_opcode(p_string[0]);

            int flag = check_reg_flags(tk_2, ANY_ADDRESSING);
            alu_op <<= 3;
            flag <<= 7;
            reg_write += (alu_op + flag);
            tmp = strint(reg_write);
            f.output_arrays[total_bytes + 2] = tmp;
        }
    }    
    return 0;
} 

int generate_alu_1_immediate(int opcode, int c_bytes, int total_bytes, char **p_string, char *tk_2, char *tk_3){
    
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;
    }
    if(c_bytes >= 2){
        if(strcasecmp(p_string[0], "cmp") == 0){
            int reg_a = get_argument_value(tk_2);
            reg_a += 128;
            tmp = strint(reg_a);
            f.output_arrays[total_bytes + 1] = tmp;
        }
    }
    if(c_bytes >= 3){
        if(strcasecmp(p_string[0], "cmp") == 0){
            int alu_op = get_alu_opcode(p_string[0]);
            alu_op <<= 3;
            tmp = strint(alu_op);
            f.output_arrays[total_bytes + 2] = tmp;
        } else{
            int reg_write = get_argument_value(tk_2);
            int alu_op = get_alu_opcode(p_string[0]);

            int flag = check_reg_flags(tk_2, ANY_ADDRESSING);
            alu_op <<= 3;
            flag <<= 7;
            reg_write += (alu_op + flag);
            tmp = strint(reg_write);
            f.output_arrays[total_bytes + 2] = tmp;
        }
        if(c_bytes == 4){
            f.output_arrays[total_bytes + 3] = strint(get_big_immediate_value(tk_3));
        }
    }    
    return 0;
} 


// MOV functions

int generate_ldi(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3){

    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 3){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 2] = tmp;    
    }
    if(c_bytes >= 4){
        f.output_arrays[total_bytes + 3] = strint(get_big_immediate_value(tk_3));
    }
    return 0;
}

int generate_rtr_ctc_rtc_ctr(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_3));
        f.output_arrays[total_bytes + 1] = tmp;    
    }
    if(c_bytes >= 3){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 2] = tmp;    
    }
    return 0;
}

int generate_rtp(int opcode, int c_bytes, int total_bytes, char *tk_2){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 1] = tmp;    
    }

    return 0;
}

// data stack instructions

int generate_psh(int opcode, int c_bytes, int total_bytes, char *tk_2){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 1] = tmp;    
    }    

    return 0;
}

int generate_pop(int opcode, int c_bytes, int total_bytes, char *tk_2){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 2] = tmp;    
    }    

    return 0;
}

// RAM instructions

int generate_cld_cst(int opcode, int c_bytes, int total_bytes, char *tk_2){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 1] = tmp;    
    }    

    return 0;
}

int generate_xld_xst(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 1] = tmp;    
    }    
    if(c_bytes >= 3){
        tmp = strint(get_argument_value(tk_3));
        f.output_arrays[total_bytes + 2] = tmp;    
    }

    return 0;
}

// IO instructions

int generate_snd(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 2){
        tmp = strint(get_argument_value(tk_3));
        f.output_arrays[total_bytes + 1] = tmp;    
    }    
    if(c_bytes >= 4){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 3] = tmp;    
    }

    return 0;
}    

int generate_rec(int opcode, int c_bytes, int total_bytes, char *tk_2, char *tk_3){
    if(c_bytes >= 1){
        tmp = generate_opcode(c_bytes, opcode);
        f.output_arrays[total_bytes] = tmp;        
    }
    if(c_bytes >= 3){
        tmp = strint(get_argument_value(tk_2));
        f.output_arrays[total_bytes + 2] = tmp;    
    }    
    if(c_bytes >= 4){
        tmp = strint(get_argument_value(tk_3));
        f.output_arrays[total_bytes + 3] = tmp;    
    }

    return 0;
}    
