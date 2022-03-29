//
// Created by kiwul on 2/18/2021.
//

#include "../headers/toPostfix.h"
#include <malloc.h>
stack_t *stack_init(stack_t *st) {
    st = (stack_t*)malloc(sizeof(stack_t));
    st->size = 1000000;
    st->amt = 0;
    st->cur = 0;
    return st;
}
void stack_free(stack_t* st){
    free(st);
}
int is_empty(stack_t* st){
    return (!st->amt);
}
int push(stack_t* st, char c) {
    if (st->amt >= st->size) // overflow
        return 0;
    if(!is_empty(st)) {
        if (st->cur < st->size) { //end of stack check
            st->cur++;
        } else {
            st->cur = 0;
        }
    }
    st->amt++;
    st->mas[st->cur] = c;
    return 1;// if succeed
}
char pop(stack_t* st) {
    if (is_empty(st)) // empty check
        return '\0';

    char buf = st->mas[st->cur];
    if(st->cur == 0 && st->amt > 1) { //end of stack check
        st->cur = st->size;
    }else if (st->cur != 0){
        st->cur--;
    }
    st->amt--;
    return buf;
}
char top(stack_t* st){
    return st->mas[st->cur];
}