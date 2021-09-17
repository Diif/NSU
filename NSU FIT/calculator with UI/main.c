#include <stdio.h>
#include "headers/generalLib.h"
#include "headers/toPostfix.h"
#include "headers/calc.h"
#include <malloc.h>
#include <string.h>
char* infix_convert(FILE*);
void calculate(const char*);
void UI(FILE** in);

int main(int argc, char** argv) {
    printf("ARGC %d\n", argc);
    FILE *in;
    if(argc > 1){
        in = fopen(argv[1],"r");
    } else {
        UI(&in);
    }
    if(in != NULL){
        char *str = infix_convert(in);
        calculate(str);
        free(str);
    }
    getchar();
    return 0;
}

void UI(FILE** in) {
    char command[39] = {0};
    char inputF[35] = {0};//TODO remove
    int len;
    *in = NULL;
    printf("\n");
    printf("\tEnter a command: -i [INPUT FILE NAME].txt\n");
    printf("\tMax command length: 38 symbols.\n\n");
    printf("\tUse command \"s\" to use default file: \"input.txt\".");
    printf("\n");
    FILE *check = stdin;
    fgets(command, 40, check);
    len = strlen(command);
    if (command[38] != '\0') {
        printf("Command is too long!");
        return;
    }
    for (int i = 0; i < len; i++) {
        if (command[i] == ' ' || command[i] == '\n') {
            continue;
        }
        if (command[i] == 's') {
            strcpy(inputF, "input.txt");
            *in = fopen(inputF, "r");
            return;
        }
        if (command[i] == '-') {
            if (command[i + 1] == 'i') {
                i++;
                if (command[i + 1] == ' ' && (i + 1) < len) {
                    i = i + 2;
                    int inlen = 0;
                    while ((command[i] != ' ' && command[i] != '\0' && command[i] != '\n') && i < len) {
                        add_char_to_str(command[i], inputF, inlen);
                        inlen++;
                        i++;
                    }
                } else {
                    printf("Incorrect command!");
                    return;
                }
            } else {
                printf("Incorrect command!");
                return;
            }
        } else {
            printf("Incorrect command!");
            return;
        }
    }
    if (inputF[0] != '\0') {
        *in = fopen(inputF, "r");
    }
}

char* infix_convert(FILE* in){
    int operand_flag = 0, open_flag = 0, len = 0;
    char buf;
    char* str = (char*)malloc(sizeof(char)*1000000);
    stack_t* st;
    st = stack_init(st);

    while ((buf = fgetc(in)) != EOF){
        if (is_operand(buf)) {
            if (buf != '\n' && buf != ' ') {
                add_char_to_str(buf, str, len);
                len++;
                operand_flag = 1;
            }
            continue;
        }
        if (operand_flag){
            open_flag = 0;
            operand_flag = 0;
            add_char_to_str(' ', str, len);
            len++;
        }

        switch (buf) {
            case '(': push(st,buf); open_flag = 1;break;
            case ')': {
                open_flag = 0;
                while (top(st) != '(') {
                    add_char_to_str(pop(st), str,len);
                    len++;
                }
                pop(st);
                break;
            }
            case '-': {//modified minus
                if (str[0] == '\0'){
                    str[0] = '0';
                    str[1] = ' ';
                } else if (top(st) == '(' && open_flag) {
                    // add_char_to_str(' ',str);
                    add_char_to_str('0',str,len);
                    len++;
                    add_char_to_str(' ',str, len);
                    len++;
                    open_flag = 0;
                }
            }
            case '+':
            case '*':
            case '/': {
                open_flag = 0;
                while (is_higher_or_eq(top(st), buf) && !is_empty(st)) {
                    add_char_to_str(pop(st), str, len);
                    len++;
                }
                push(st, buf);
                break;
            }
            default: break;
        }
    }

    while(!is_empty(st)) {
        add_char_to_str(pop(st), str, len);
        len++;
    }


    stack_free(st);

    return str;
}

void calculate(const char* str) {

    int operand_flag = 0, vallen = 0;
    char value[5] = {0};
    char buf;

    stack_t2 *st;
    st = stack_init2(st);

    for (int i = 0; str[i] != '\0'; i++) {
        buf = str[i];
        if (is_operand(buf) && buf != ' ') {
            operand_flag = 1;
            add_char_to_str(buf,value,vallen);
            vallen++;
            continue;
        }

        if(operand_flag){
            operand_flag = 0;
            push_from_str(st,value);
            for(int j = 0; j < 5; j++){
                if(value[j] == '\0'){
                    break;
                }
                value[j] = '\0';
                vallen = 0;
            }
        }
        if(buf == ' '){
            continue;
        }

        char op = str[i];
        double last = pop2(st); //TODO use long long if needed
        double plast = pop2(st);
        switch (op) {
            case '+':
                last = last + plast;
                push_from_double(st, last);
                break;
            case '-':
                last = plast - last;
                push_from_double(st, last);
                break;
            case '*':
                last = plast * last;
                push_from_double(st, last);
                break;
            case '/':
                last = plast / last;
                push_from_double(st, last);
                break;
        }
    }
    printf("%.20lf", pop2(st));
    stack_free2(st);
}
