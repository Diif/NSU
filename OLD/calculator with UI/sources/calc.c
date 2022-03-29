//
// Created by kiwul on 2/18/2021.
//

#include "../headers/calc.h"
#include <stdlib.h>

stack_t2* stack_init2(stack_t2* st){
    st = (stack_t2*)malloc(sizeof(stack_t2));
    st->size = 500000;
    st->amt = 0;
    st->cur = 0;
    return st;
}
void stack_free2(stack_t2* st){
    free(st);
}
int push_from_str(stack_t2* st, char* str){
    if (st->amt >= st->size) // overflow
        return 0;
    if(!is_empty2(st)) {
        if (st->cur < (st->size-1)) { //end of stack check
            st->cur++;
        } else {
            st->cur = 0;
        }
    }
    st->amt++;
    st->mas[st->cur] = atoi(str);
    return 1;// if succeed
}

int push_from_double(stack_t2* st, double num)
{
    if (st->amt >= st->size) // overflow
        return 0;
    if(!is_empty2(st)) {
        if (st->cur < ((st->size)-1)) { //end of stack check
            st->cur++;
        } else {
            st->cur = 0;
        }
    }
    st->amt++;
    st->mas[st->cur] = num;
    return 1;// if succeed
}
double pop2(stack_t2* st){
    if (is_empty2(st)) // empty check
        return 0;

    double buf = st->mas[st->cur];
    if(st->cur == 0 && !(is_empty2(st))) { //end of stack check
        st->cur = st->size - 1;
    }else if (st->cur != 0){
        st->cur--;
    }
    st->amt--;
    return buf;
}
int is_empty2(stack_t2* st){
    return (!st->amt);
}
