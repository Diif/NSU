#include <stdio.h>
#include <malloc.h>
#include <string.h>
//hard-coded stack
typedef  struct char_stack{
    char mas[1001];
    int amt;
    int cur;
    int size;
}stack_t;

stack_t* stack_init(stack_t* st){
    st = (stack_t*)malloc(sizeof(stack_t));
    st->size = 1001;
    st->amt = 0;
    st->cur = 0;
    return st;
}

void stack_free(stack_t* st){
    free(st);
}

int set_priority(char c){
    switch (c) {
        case '(': c = 1;break;
        case ')': c = 2;break;
        case '+': c = 4;break;
        case '-': c = 4;break;
        case '*': c = 5;break;
        case '/': c = 5;break;
        default: return -1;
    }
    return (int)c;
}
int is_operand(char c){
    switch (c) {
        case '(': c = 0;break;
        case ')': c = 0;break;
        case '+': c = 0;break;
        case '-': c = 0;break;
        case '*': c = 0;break;
        case '/': c = 0;break;
        default: return 1;
    }
    return (int)c;
}
int is_higher_or_eq(char one, char two){
    int ione = set_priority(one);
    int itwo = set_priority(two);
   /* if(ione == -1 || itwo == -1){
        printf("%s", "smth is wrong!");
    }*/
    return (ione >= itwo);
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

void add_char_to_str(char c, char* str){ //TODO optimize if needed
    int len = strlen(str);
        str[len] = c;
}

int main() {
    freopen("input.txt", "r",stdin);
    freopen("output.txt","w",stdout);

    char buf;
    char str[1002] = {0};
    stack_t* st;
    st = stack_init(st);

    while (scanf("%c", &buf) > 0){

        if (is_operand(buf)) {
            if (buf != '\n')
            add_char_to_str(buf, str);
            continue;
        }

        switch (buf) {
            case '(': push(st,buf);break;
            case ')': {
                while (top(st) != '(') {
                    add_char_to_str(pop(st), str);
                }
                pop(st);
                break;
            }
            case '+':
            case '-':
            case '*':
            case '/': {
                while (is_higher_or_eq(top(st), buf) && !is_empty(st)) {
                    add_char_to_str(pop(st), str);
                }
                push(st, buf);
                break;
            }
            default: break;
        }
    }


    while(!is_empty(st))
        add_char_to_str(pop(st),str);

    printf("%s", str);

    //TODO add free if needed
    return 0;
}
