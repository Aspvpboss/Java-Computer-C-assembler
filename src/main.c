#include "common.h"
File_Info f;
Token_Info t;
Label_Info l;
Set_Vars set;



int main(void){  
    
    if(init_files(&f, &t)){        
        printf("ERROR_FUNCTION: init_files\n"); 
        printf("unsuccessful assembled\n");
        free_memory(&f, &t); 
        return 1;
    }


    if(tokenize()){
        printf("ERROR_FUNCTION: tokenize\n");
        printf("unsuccessful assembled\n");
        free_memory(&f, &t);
        return 1;
    }



    if(parse()){
        printf("ERROR_FUNCTION: parse\n");
        printf("unsuccessful assembled\n");
        free_memory(&f, &t);
        return 1;        
    }



    if(generate()){
        printf("ERROR_FUNCTION: generate\n");
        printf("unsuccessful assembled\n");
        free_memory(&f, &t);
        return 1;           
    } 
    printf("\n");
    
    free_memory(&f, &t);

    printf("\n");
    printf("successful assembled\n");
    return 0;
}
