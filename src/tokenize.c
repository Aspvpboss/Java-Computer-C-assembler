#include "tokenize.h"
char **init(){
    char **tmp_file_data = malloc(sizeof(char*) * f.file_lines);

    for(int i = 0; i < f.file_lines; i++)

        tmp_file_data[i] = malloc(sizeof(char) * 200);  
    return tmp_file_data;  
}



void free_memory_2(char **tmp_file_data){
    for(int i = 0; i < f.file_lines; i++)

        free(tmp_file_data[i]);

    free(tmp_file_data);    
}



void get_lines(char **array){
    for(int i = 0; i < f.file_lines; i ++){
        fgets(array[i], 200, f.file_in);
        array[i][strcspn(array[i], "\n")] = 0;
    }
}



int get_tokens(char **file_data){

    //c_line is current line being tokenized

    int tmp_file_lines = f.file_lines;
    f.file_lines = 0;

    for(int c_line = 0; c_line < tmp_file_lines; c_line++){
        
        int amount_tokens = 0;

        //if line is empty, skip line
        char *token = strtok(file_data[c_line], " ");
        if(token == NULL){
            continue;
        }
        if(strrchr(token, ';')){
            amount_tokens--;
            continue;
        }
        f.file_lines++;
        t.num_tokens = realloc(t.num_tokens, sizeof(int) * f.file_lines);



        amount_tokens++;

        f.file_arrays = realloc(f.file_arrays, sizeof(char**) * f.file_lines);
        f.file_arrays[f.file_lines - 1] = malloc(sizeof(char*) * amount_tokens);
        f.file_arrays[f.file_lines - 1][amount_tokens - 1] = malloc(sizeof(char) * f.file_array_size);

        if(strlen(token) > f.file_array_size){
            printf("ERROR: token '%s' in line '%d' is %d characters long, max is %d characters long\n", token, c_line + 1, strlen(token), f.file_array_size);
            return 1;
        }

        strcpy(f.file_arrays[f.file_lines - 1][amount_tokens - 1], token);


        
        while((token = strtok(NULL, " ")) != NULL){
            
            amount_tokens++;
            if(strrchr(token, ';')){
                amount_tokens--;
                break;
            }

            f.file_arrays[f.file_lines - 1] = realloc(f.file_arrays[f.file_lines - 1], sizeof(char*) * amount_tokens);
            f.file_arrays[f.file_lines - 1][amount_tokens - 1] = malloc(sizeof(char) * f.file_array_size);

            if(strlen(token) > f.file_array_size){
                printf("ERROR: token '%s' in line '%d' is %d characters long, max is %d characters long\n", token, c_line + 1, strlen(token), f.file_array_size);
                return 1;
            }
            
            strcpy(f.file_arrays[f.file_lines - 1][amount_tokens - 1], token);

        }
        t.num_tokens[f.file_lines - 1] = amount_tokens;
    
    }
    return 0;
}


//tokenize.c
int tokenize(){
    char **tmp_file_data = init();
    get_lines(tmp_file_data);


    if(get_tokens(tmp_file_data))
        return 1;


    free_memory_2(tmp_file_data);
    return 0;
}