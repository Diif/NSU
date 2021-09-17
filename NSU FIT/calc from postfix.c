#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

//hard-coded stack
typedef  struct char_stack{
    int mas[2002]; //TODO long long maybe?
    int amt;
    int cur;
    int size;
}stack_t;

stack_t* stack_init(stack_t* st){
    st = (stack_t*)malloc(sizeof(stack_t));
    st->size = 2002;
    st->amt = 0;
    st->cur = 0;
    return st;
}

void stack_free(stack_t* st){
    free(st);
}
int is_operand(char* c){
    switch (c[0]) {
        case '+':
        case '-':
        case '*':
        case '/': return 0;
        default: return 1;
    }
}
int is_empty(stack_t* st){
    return (!st->amt);
}

int push_from_str(stack_t* st, char* str) {
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
    st->mas[st->cur] = atoi(str);
    return 1;// if succeed
}
int push_from_int(stack_t* st, int num) {
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
    st->mas[st->cur] = num;
    return 1;// if succeed
}
int pop(stack_t* st) {
    if (is_empty(st)) // empty check
        return 0;

    int buf = st->mas[st->cur];
    if(st->cur == 0 && st->amt > 1) { //end of stack check
        st->cur = st->size;
    }else if (st->cur != 0){
        st->cur--;
    }
    st->amt--;
    return buf;
}

int top(stack_t* st){
    return st->mas[st->cur];
}

int main() {
    freopen(PATH"/input.txt", "r",stdin);
    freopen(PATH"/output.txt","w",stdout);

    char str[2002] = {0};
    int ibuf = 0;
    char buf;

    stack_t* st;
    st = stack_init(st);

    while (scanf("%s", str) > 0 && str[0] != '\n') {

        if(is_operand(str)){
            push_from_str(st,str);
            continue;
        }

        char op = str[0];
        int last = pop(st); //TODO use long long if needed
        int plast = pop(st);
        switch (op) {
            case '+':
                last = last+plast;
                push_from_int(st,last); break;
            case '-':
                last = plast-last;
                push_from_int(st,last); break;
            case '*':
                last = plast*last;
                push_from_int(st,last); break;
            case '/':
                last = plast/last;
                push_from_int(st,last); break;
        }
    }

    printf("%d", pop(st));
    //TODO add free if needed */
    return 0;
}
