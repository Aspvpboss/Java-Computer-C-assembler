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

            generate_ldi(15, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(LDI_INDIRECT_3):

            generate_ldi(16, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTC_DIRECT):

            generate_rtr_ctc_rtc_ctr(17, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTC_INDIRECT_2):

            generate_rtr_ctc_rtc_ctr(18, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTC_INDIRECT_3):

            generate_rtr_ctc_rtc_ctr(19, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTR_DIRECT):

            generate_rtr_ctc_rtc_ctr(20, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTR_INDIRECT_2):

            generate_rtr_ctc_rtc_ctr(21, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTR_INDIRECT_3):

            generate_rtr_ctc_rtc_ctr(22, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTP_DIRECT):

            generate_rtp(23, c_bytes, total_bytes, tk_3);

            break;

        case(RTP_INDIRECT_2):

            generate_rtp(24, c_bytes, total_bytes, tk_3);

            break;

        case(CTR_DIRECT):

            generate_rtr_ctc_rtc_ctr(25, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTR_INDIRECT_2):

            generate_rtr_ctc_rtc_ctr(26, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTR_INDIRECT_3):

            generate_rtr_ctc_rtc_ctr(27, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(CTR_INDEX):

            generate_rtr_ctc_rtc_ctr(28, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTC_DIRECT):

            generate_rtr_ctc_rtc_ctr(29, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(RTC_INDIRECT_2):

            generate_rtr_ctc_rtc_ctr(30, c_bytes, total_bytes, tk_2, tk_3);    

            break;

        case(RTC_INDIRECT_3):

            generate_rtr_ctc_rtc_ctr(31, c_bytes, total_bytes, tk_2, tk_3);    

            break;

        case(RTC_INDEX):

            generate_rtr_ctc_rtc_ctr(32, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(PSH_DIRECT):

            generate_psh(33, c_bytes, total_bytes, tk_2);

            break;

        case(PSH_INDIRECT_2):

            generate_psh(34, c_bytes, total_bytes, tk_2);

            break;

        case(POP_DIRECT):

            generate_pop(35, c_bytes, total_bytes, tk_2);

            break;

        case(POP_INDIRECT_3):

            generate_pop(36, c_bytes, total_bytes, tk_2);

            break;

        case(CLD_DIRECT):

            generate_cld_cst(37, c_bytes, total_bytes, tk_2);

            break;

        case(CLD_INDIRECT_2):

            generate_cld_cst(38, c_bytes, total_bytes, tk_2);

            break;

        case(CST_DIRECT):

            generate_cld_cst(39, c_bytes, total_bytes, tk_2);

            break;

        case(CST_INDIRECT_2):

            generate_cld_cst(40, c_bytes, total_bytes, tk_2);

            break;

        case(XLD_DIRECT):

            generate_xld_xst(41, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(XLD_INDIRECT_2):

            generate_xld_xst(42, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(XLD_INDIRECT_3):

            generate_xld_xst(43, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(XST_DIRECT):

            generate_xld_xst(44, c_bytes, total_bytes, tk_3, tk_2);

            break;

        case(XST_INDIRECT_2):

            generate_xld_xst(45, c_bytes, total_bytes, tk_3, tk_2);

            break;

        case(XST_INDIRECT_3):

            generate_xld_xst(46, c_bytes, total_bytes, tk_3, tk_2);

            break;

        case(SND_DIRECT):

            generate_snd(47, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(SND_INDIRECT_2):

            generate_snd(48, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(SND_INDEX):

            generate_snd(49, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(REC_DIRECT):

            generate_rec(50, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(REC_INDIRECT_3):

            generate_rec(51, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(REC_INDEX):

            generate_rec(52, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(WRE_DIRECT):

            generate_rec(53, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(WRE_INDIRECT_3):

            generate_rec(54, c_bytes, total_bytes, tk_2, tk_3);

            break;

        case(WRE_INDEX):

            generate_rec(55, c_bytes, total_bytes, tk_2, tk_3);

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