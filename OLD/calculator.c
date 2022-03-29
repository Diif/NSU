#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
//hard-coded stack

typedef  struct int_stack{
    double mas[500000]; //TODO long long maybe?
    int amt;
    int cur;
    int size;
}stack_t2;

typedef  struct char_stack{
    char mas[1000000];
    int amt;
    int cur;
    int size;
}stack_t;

int is_empty2(stack_t2* st);
void part2(const char*);
stack_t2* stack_init2(stack_t2*);
int push_from_str(stack_t2*, char*);
int push_from_double(stack_t2*, double);
double pop2(stack_t2*);


stack_t* stack_init(stack_t* st){
    st = (stack_t*)malloc(sizeof(stack_t));
    st->size = 1000000;
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

void add_char_to_str(char c, char* str, int len){ //TODO optimize if needed
    str[len] = c;
    str[len+1] = '\0';
}

int main() {
    freopen(PATH"/input.txt", "r",stdin);
    freopen(PATH"/output.txt","w",stdout);
    int operand_flag = 0, open_flag = 0, len = 0;
    char buf;
    char str[1000000] = {0};
    stack_t* st;
    st = stack_init(st);

    while (scanf("%c", &buf) > 0){
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

  // printf("%s", str);
    stack_free(st);
    part2(str);


    //TODO add free if needed
    return 0;
}

void part2(const char* str) {

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
    double bruh =  pop2(st);
  /*  if (bruh == -0 ){
        bruh  = 0;
    }*/
    printf("%.20lf", bruh);
}

stack_t2* stack_init2(stack_t2* st){
    st = (stack_t2*)malloc(sizeof(stack_t2));
    st->size = 500000;
    st->amt = 0;
    st->cur = 0;
    return st;
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