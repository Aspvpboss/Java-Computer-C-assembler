#include "init.h"


//init.c
int init_files(File_Info *f, Token_Info *t){

    f->file_array_size = 70;
    
    f->file_in = fopen("program.txt", "r");
    f->file_out = fopen("output.txt", "w");



    if(f->file_in == NULL){
        printf("failed to open program.txt\n");
        return 1;
    }
    if(f->file_out == NULL){
        printf("failed to open output.txt\n");
        return 1;
    }



    //lines in program.txt
    f->file_lines = 0;
    char *tmp = malloc(sizeof(char) * 200);

    while(fgets(tmp, 200, f->file_in))
        f->file_lines++;

    free(tmp);
    if(f->file_lines == 0){
        printf("ERROR: no text in program.txt\n");
        return 1;
    }

    
    fseek(f->file_in, 0, SEEK_SET);
    return 0;
}

//init.c
void free_memory(File_Info *f, Token_Info *t){

    for(int x = 0; x < f->file_lines; x++){
        for(int y = 0; y < t->num_tokens[x]; y++){
            free(f->file_arrays[x][y]);
        }
        free(f->file_arrays[x]);
    }

    for(int i = 0; i < set.num_macros; i++){
        free(set.macro_name[i]);
        free(set.macro[i]);
    }
    free(set.macro_name);
    free(set.macro);

    for(int i = 0; i < l.num_labels; i++){
        free(l.label_strings[i]);
    }
    free(l.label_strings);
    free(l.label_addresses);


    free(f->file_arrays);
    free(t->num_tokens);    
    free(t->num_bytes);
    free(t->instruction_array);
    free(t->opcode_array);
    fclose(f->file_in);
    fclose(f->file_out);

}