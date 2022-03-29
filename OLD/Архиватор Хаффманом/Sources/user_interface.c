//
// Created by kiwul on 5/18/2021.
//
#include "../Headers/general.h"
#include "../Headers/user_interface.h"
#include "../Headers/huff.h"

void UI(int *argc, char** args) {
    int num_args = *argc;
    if(num_args < 3) {//запрос при нехватке аргументов
        for (int i = 0; i < num_args; ++i) {
            free(args[i]);
        }
        print_commands();
        free(args);
        args = get_args(argc);
        num_args = *argc;
    }
    if(num_args == 3){//при 3 аргументах либо извлечение, либо информация
        char command = get_command(args[1]);
        if(command != 'l' && command != 't' && command !='x'){
            error_message(ERROR_COMMAND);
        }
        check_arc_ext(args[2]);
        if(command == 'l') {
            char **name = (char **) malloc(sizeof(char *));
            i64 size;
            char cmp;
            FILE *in = fopen(args[2], "rb");
            get_file_info(name, &size, &cmp, in);
            printf("\n\tFile info:\n\t\tname: %s\n\t\tsize: %llu bites\n\t\tcompression: %d %% of original", name[0], size, cmp);
        } else if (command == 'x'){
            FILE *in = fopen(args[2], "rb");
            decode(in);
        }
    }
    if(num_args > 3){//случай архивирования
        check_arc_ext(args[2]);
        char command = get_command(args[1]);
        if(command == 'a') {
            FILE *in = fopen(args[3], "rb");
            if(!in){
                error_message(ERROR_N_EXISTS);
            }
            FILE *out = fopen(args[2], "wb");
            encode(in, out, args[3]);
        }
    }
}

void print_greetings(){
    printf("\n\n\t\t\t*************************\n");
    printf("\n\n\t\t\t***Archiver. Archives.***\n");
    printf("\n\n\t\t\t*************************\n\n");
}

void print_commands(){
    printf("\tEnter a command: -[FLAG] [ARCHIVE.arc] [FILE.ext]\n");
    printf("\t\tList of flags:\n\t\t  a - put files\n\t\t  x - extract files\n\t\t  d - remove files\n\t\t  l - information about files\n\t\t  t - check arc hash-sum\n\n");
}


void check_arc_ext(char* arc){
    int len = strlen(arc);
    if(len < 5){
        error_message(ERROR_EXT);
    }
    arc--;
    if(arc[len] != 'c' || arc[len-1] !='r' || arc[len-2] != 'a' || arc[len-3] != '.'){
        error_message(ERROR_EXT);
    }
}

char get_command(const char* flag){
    if(flag[0] != '-' || flag[2] !='\0'){
        error_message(ERROR_FLAG);
    }
    switch(flag[1]){
        case 'a': return 'a';
        case 'x': return 'x';
        case 'd': return 'd';
        case 'l': return 'l';
        case 't': return 't';
        default: error_message(ERROR_FLAG);
    }
}

int get_word_len(char* str){
    int i;
    for (i = 0; str[i] != ' ' && str[i] != '\n' && str[i] != '\0' ; ++i) {    }
    str[i] = '\0';
    return i;
}

char** get_args(int* argc){
    char buf[5000];
    int len;
    int total_len;
    char **res = (char**)malloc(sizeof(char*)*100);
    for (int i = 0; i < 100; ++i) {
        res[i] =  NULL;
    }
    *argc = 1;
    res[0] = (char*)malloc(sizeof(char)*9);
    strcpy(res[0],"harc.exe");
    gets(buf);
    total_len = strlen(buf);
    for (int i = 1, j = 0;j < total_len; j++){
        if(buf[j] == ' ' || buf[j] == '\0'){
            continue;
        }
        len = get_word_len(&(buf[j]));//считывает длину слова, не строки
        res[i] = (char*)malloc(sizeof(char)*(len+1));//для нулевого символа
        strcpy(res[i],&(buf[j]));
        (*argc)++;
        j+=len;
        i++;
    }
    return res;
}
