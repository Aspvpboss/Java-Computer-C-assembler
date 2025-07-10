#include "generate.h"
#include "generate_func.h"


// returns 0 if successful
int get_binary(Opcode_Type opcode, char **p_string, int c_bytes, int total_bytes, int c_line){

    char *tk_2 = NULL;
    char *tk_3 = NULL;
    char *tk_4 = NULL;
    char *tmp = NULL;

    if(total_bytes > 1023){
        printf("ERROR: tried to addressing memory that doesn't exist, max is 1023, tried to address %d\n", total_bytes);
        return 1;
    }



    if(t.num_tokens[c_line] >= 2){
        tk_2 = p_string[TOKEN_TWO];
    }
    if(t.num_tokens[c_line] >= 3){
        tk_3 = p_string[TOKEN_THREE];
    }
    if(t.num_tokens[c_line] >= 4){
        tk_4 = p_string[TOKEN_FOUR];
    }


    switch (opcode){
        
        case(NONE):

            break;

        case(LABEL_STRING):

            break;

        case(LABEL_INT):

            break;

        case(HLT_DIRECT):
    
            if(c_bytes > 0){
                tmp = strint(0);
                f.output_arrays[total_bytes] = tmp;
            }
            break;

        case(NOP_DIRECT):
    
            if(c_bytes > 0){
                tmp = strint(1);
                f.output_arrays[total_bytes] = tmp;
            }
            break;

        case(ALU_1):

            generate_alu_1(2, c_bytes, total_bytes, p_string, tk_2, tk_3);

            break;

        case(ALU_1_IMMEDIATE):

            generate_alu_1_immediate(3, c_bytes, total_bytes, p_string, tk_2, tk_3);

            break;

        case(ALU_2):
            
            generate_alu_2(2, c_bytes, total_bytes, p_string, tk_2, tk_3, tk_4);

            break;

        case(ALU_2_IMMEDIATE):

            generate_alu_2_immediate(3, c_bytes, total_bytes, p_string, tk_2, tk_3, tk_4);

            break;

        case(LDI_DIRECT):

            break;

        case(LDI_INDIRECT_3):

            break;

        case(CTC_DIRECT):

            break;

        case(CTC_INDIRECT_2):

            break;

        case(CTC_INDIRECT_3):

            break;

        case(RTR_DIRECT):

            break;

        case(RTR_INDIRECT_2):

            break;

        case(RTR_INDIRECT_3):

            break;

        case(RTP_DIRECT):

            break;

        case(RTP_INDIRECT_2):

            break;

        case(CTR_DIRECT):

            break;

        case(CTR_INDIRECT_2):

            break;

        case(CTR_INDIRECT_3):

            break;

        case(CTR_INDEX):

            break;

        case(RTC_DIRECT):

            break;

        case(RTC_INDIRECT_2):

            break;

        case(RTC_INDIRECT_3):

            break;

        case(RTC_INDEX):

            break;

        case(PSH_DIRECT):

            break;

        case(PSH_INDIRECT_2):

            break;

        case(POP_DIRECT):

            break;

        case(POP_INDIRECT_3):

            break;

        case(CLD_DIRECT):

            break;

        case(CLD_INDIRECT_2):

            break;

        case(CST_DIRECT):

            break;

        case(CST_INDIRECT_2):

            break;

        case(XLD_DIRECT):

            break;

        case(XLD_INDIRECT_2):

            break;

        case(XLD_INDIRECT_3):

            break;

        case(XST_DIRECT):

            break;

        case(XST_INDIRECT_2):

            break;

        case(XST_INDIRECT_3):

            break;

        case(SND_DIRECT):

            break;

        case(SND_INDIRECT_2):

            break;

        case(SND_INDEX):

            break;

        case(REC_DIRECT):

            break;

        case(REC_INDIRECT_3):

            break;

        case(REC_INDEX):

            break;

        case(WRE_DIRECT):

            break;

        case(WRE_INDIRECT_3):

            break;

        case(WRE_INDEX):

            break;

        case(JMP_DIRECT):
        
            break;

        case(JMP_INDIRECT_3):

            break;

        case(JIF_DIRECT):

            break;

        case(JIF_INDIRECT_2):

            break;

        case(JIF_INDIRECT_3):

            break;

        case(CAL_DIRECT):

            break;

        case(CAL_INDIRECT_3):

            break;

        case(CIF_DIRECT):

            break;

        case(CIF_INDIRECT_2):

            break;

        case(CIF_INDIRECT_3):

            break;

        case(RET):

            break;
    }

    return 0;
}



int generate_binary(){
    int total_bytes = 0;
    int c_bytes = 0;
    int result;

    for(int c_line = 0; c_line < f.file_lines; c_line++){
        c_bytes = t.num_bytes[c_line];
        if(t.instruction_array[c_line] == AT_ADDRESS){
            total_bytes = get_big_immediate_value(f.file_arrays[c_line][TOKEN_TWO]); 
        }

        result = get_binary(t.opcode_array[c_line], f.file_arrays[c_line], c_bytes, total_bytes, c_line);
        
        if(result){
            return 1;
        }

        total_bytes += c_bytes;
    }

    return 0;
}



int print_binary(){
    for(int i = 0; i < MAX_BYTES; i++){
        fprintf(f.file_out, "%s\n", f.output_arrays[i]);
    }
    return 0;
}



int generate(){

    if(generate_binary()){
        printf("ERROR: generate_binary()\n");
        return 1;
    }

    if(print_binary()){
        printf("ERROR: print_binary()\n");
        return 1;        
    }

    return 0;
}