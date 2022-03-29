//
// Created by kiwul on 2/18/2021.
//

#ifndef LAB_CALC_H
#define LAB_CALC_H

typedef  struct int_stack{
    double mas[500000]; //TODO long long maybe?
    int amt;
    int cur;
    int size;
}stack_t2;

int is_empty2(stack_t2* st);
void stack_free2(stack_t2* st);
stack_t2* stack_init2(stack_t2*);
int push_from_str(stack_t2*, char*);
int push_from_double(stack_t2*, double);
double pop2(stack_t2*);

#endif //LAB_CALC_H
