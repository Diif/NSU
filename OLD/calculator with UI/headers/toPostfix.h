//
// Created by kiwul on 2/18/2021.
//

#ifndef LAB_TOPOSTFIX_H
#define LAB_TOPOSTFIX_H

typedef  struct char_stack{
    char mas[1000000];
    int amt;
    int cur;
    int size;
}stack_t;

stack_t* stack_init(stack_t* st);
void stack_free(stack_t* st);
int is_empty(stack_t* st);
int push(stack_t* st, char c);
char pop(stack_t* st);
char top(stack_t* st);

#endif //LAB_TOPOSTFIX_H
