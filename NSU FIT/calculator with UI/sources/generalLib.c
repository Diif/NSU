//
// Created by kiwul on 2/18/2021.
//

#include "../headers/generalLib.h"

int set_priority(char c){
    switch (c) {
        case '(': c = 1;break;
        case ')': c = 2;break;
        case '+':
        case '-': c = 4;break;
        case '*':
        case '/': c = 5;break;
        default: return -1;
    }
    return (int)c;
}
int is_operand(char c){
    switch (c) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/': c = 0;break;
        default: return 1;
    }
    return (int)c;
}
int is_higher_or_eq(char one, char two){
    int ione = set_priority(one);
    int itwo = set_priority(two);
    return (ione >= itwo);
}

void add_char_to_str(char c, char* str, int len){
    str[len] = c;
    str[len+1] = '\0';
}