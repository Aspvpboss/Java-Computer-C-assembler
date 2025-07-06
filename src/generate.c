#include "generate.h"




int generate(Opcode_Type opcode, int c_line, int c_byte){

    switch (opcode){
        
        case(NONE):

            return 0;

        case(LABEL_STRING):

            return 0;

        case(LABEL_INT):

            return 0;

        case(HLT_DIRECT):

            return 0;

        case(NOP_DIRECT):

            return 0;

        case(ALU_1):

            return 0;

        case(ALU_1_IMMEDIATE):

            return 0;

        case(ALU_1_FLAG):

            return 0;

        case(ALU_1_IMMEDIATE_FLAG):

            return 0;

        case(ALU_2):

            return 0;

        case(ALU_2_IMMEDIATE):

            return 0;

        case(ALU_2_FLAG):

            return 0;

        case(ALU_2_IMMEDIATE_FLAG):

            return 0;

        case(LDI_DIRECT):

            return 0;

        case(LDI_INDIRECT_3):

            return 0;

        case(CTC_DIRECT):

            return 0;

        case(CTC_INDIRECT_2):

            return 0;

        case(CTC_INDIRECT_3):

            return 0;

        case(RTR_DIRECT):

            return 0;

        case(RTR_INDIRECT_2):

            return 0;

        case(RTR_INDIRECT_3):

            return 0;

        case(RTP_DIRECT):

            return 0;

        case(RTP_INDIRECT_2):

            return 0;

        case(CTR_DIRECT):

            return 0;

        case(CTR_INDIRECT_2):

            return 0;

        case(CTR_INDIRECT_3):

            return 0;

        case(CTR_INDEX):

            return 0;

        case(RTC_DIRECT):

            return 0;

        case(RTC_INDIRECT_2):

            return 0;

        case(RTC_INDIRECT_3):

            return 0;

        case(RTC_INDEX):

            return 0;

        case(PSH_DIRECT):

            return 0;

        case(PSH_INDIRECT_2):

            return 0;

        case(POP_DIRECT):

            return 0;

        case(POP_INDIRECT_3):

            return 0;

        case(CLD_DIRECT):

            return 0;

        case(CLD_INDIRECT_2):

            return 0;

        case(CST_DIRECT):

            return 0;

        case(CST_INDIRECT_2):

            return 0;

        case(XLD_DIRECT):

            return 0;

        case(XLD_INDIRECT_2):

            return 0;

        case(XLD_INDIRECT_3):

            return 0;

        case(XST_DIRECT):

            return 0;

        case(XST_INDIRECT_2):

            return 0;

        case(XST_INDIRECT_3):

            return 0;

        case(SND_DIRECT):

            return 0;

        case(SND_INDIRECT_2):

            return 0;

        case(SND_INDEX):

            return 0;

        case(REC_DIRECT):

            return 0;

        case(REC_INDIRECT_3):

            return 0;

        case(REC_INDEX):

            return 0;

        case(WRE_DIRECT):

            return 0;

        case(WRE_INDIRECT_3):

            return 0;

        case(WRE_INDEX):

            return 0;

        case(JMP_DIRECT):
        
            return 0;

        case(JMP_INDIRECT_3):

            return 0;

        case(JIF_DIRECT):

            return 0;

        case(JIF_INDIRECT_2):

            return 0;

        case(JIF_INDIRECT_3):

            return 0;

        case(CAL_DIRECT):

            return 0;

        case(CAL_INDIRECT_3):

            return 0;

        case(CIF_DIRECT):

            return 0;

        case(CIF_INDIRECT_2):

            return 0;

        case(CIF_INDIRECT_3):

            return 0;

        case(RET):

            return 0;
    }

    return 0;
}