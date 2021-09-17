#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct list_element{
    int val;
    struct list_element* next;
    struct list_element* prev;
}el_s;

el_s* el_create(int val){
    el_s* buf = (el_s*)malloc(sizeof(el_s));
    buf->val = val;
    buf->next = NULL;
    buf->prev = NULL;
    return buf;
}


typedef struct list_stack{
    el_s* top;
    el_s* bot;
    int amt;
}stack_s;

int s_is_empty(stack_s* st, int init){
    if(!init) {
        return !st->amt;
    } else {
        return !(st->top);
    }
}

void s_add_bot(stack_s* st, el_s* el, int init){
    if (!st->bot) {
        st->bot = el;
        st->top = el;
        st->bot->next = NULL;
        st->bot->prev = NULL;
    } else {
        st->bot->prev = el;
        el->prev = NULL;
        el->next = st->bot;
        st->bot = el;
    }
    if(!init)
        st->amt++;
    return;
}

el_s* s_rem_bot(stack_s* st){
    if (s_is_empty(st,0)){
        return NULL;
    } else {
        el_s *buf = st->bot;
        st->bot = st->bot->next;
        if (!s_is_empty(st, 0) && st->amt > 1) {
            st->bot->prev = NULL;
        } else {
            st->top = NULL;
        }
        st->amt--;
        buf->prev = NULL;
        buf->next = NULL;
        return buf;
    }
}

void s_add_top(stack_s* st, el_s* el, int init){
    if (s_is_empty(st,init)){
        st->top = el;
        st->bot = el;
        st->top->next = NULL;
        st->top->prev = NULL;
    } else{
        st->top->next = el;
        el->next = NULL;
        el->prev = st->top;
        st->top = el;
    }
    if(!init)
        st->amt++;
    return;
}

el_s* s_rem_top(stack_s* st){
    if (s_is_empty(st,0)){
        return NULL;
    } else {
        el_s* buf = st->top;
        st->top = st->top->prev;
        if (!s_is_empty(st,0) && st->amt > 1) {
            st->top->next = NULL;
        } else {
            st->bot = st->top;
        }
        st->amt--;
        buf->prev = NULL;
        buf->next = NULL;
        return buf;
    }
}

void s_read_and_free(stack_s* st){
    if(s_is_empty(st,0)){
        printf("%d\n", 0);
        return;
    }
    el_s* buf;
    printf("%d ", st->amt);
    while (st->amt > 0){
        buf = s_rem_top(st);
        if(buf)
        printf("%d ", buf->val);
        if(buf)
            free(buf);
    }
    printf("\n");
    return;
}

void s_init(stack_s* st, int n){
    el_s* buf;

    st->amt = n;
    if(st->amt < 0)
        st->amt = -n;
    st->top = NULL;
    st->bot = NULL;
    if(n > 0) {
        while (n > 0) {
            buf = el_create(n);
            s_add_top(st, buf,1);
            n--;
        }
    } else {
        while(n < 0){
            buf = el_create(n);
            s_add_top(st,buf,1);
            n++;
        }
    }
}

char* get_op(char c){
    //brutal force!
    switch (c) {
        case '1':return "0001";
        case '2':return "0010";
        case '3':return "0011";
        case '4':return "0100";
        case '6':return "0110";
        case '7':return "0111";
        case '8':return "1000";
        case '9':return "1001";
        case 'B':return "1011";
        case 'C':return "1100";
        case 'D':return "1101";
        case 'E':return "1110";
    }
}
int skip(char c){
    if (c == 'A' || c == '0' || c == 'F' || c == '5')
        return 1;
    return 0;
}
int main() {
    freopen(PATH"/input.txt", "r", stdin);
    freopen(PATH"/output.txt", "w", stdout);

    stack_s* sl = (stack_s*)malloc(sizeof(stack_s));
    stack_s* sr = (stack_s*)malloc(sizeof(stack_s));
    el_s* elbuf;
    elbuf = el_create(324234);
    int n,m,flag;
    char buf;
    char str[5];

    scanf("%d%d", &n,&m);

    s_init(sl,n);
    s_init(sr,-n);
    int test = sizeof(*sl);
    int test2 = sizeof(*sr);
    long long testt = sizeof(*elbuf);
    for(; m > 0; m--){
        scanf("%c", &buf);
        if (buf == '\n'){
            m++;
            continue;
        }
        if (skip(buf)){
            continue;
        }

        strcpy(str, get_op(buf));
            //from left either right?
            if(str[0] == '0'){ // left!
                //from bot either top?
                if (str[1] == '0') // top
                {
                    elbuf = s_rem_top(sl);
                    if (!elbuf)
                        continue;
                }
                else if (str[1] == '1') // bot
                {
                    elbuf = s_rem_bot(sl);
                    if (!elbuf)
                        continue;
                }
            } else { // right
                if (str[1] == '0') //top
                {
                    elbuf = s_rem_top(sr);
                    if (!elbuf)
                        continue;
                }
                else if (str[1] == '1') //bot
                {
                    elbuf = s_rem_bot(sr);
                    if (!elbuf)
                        continue;
                }
            }
        //to left either right?
            if(str[2] == '0'){ // left!
                //to bot either top?
                if (str[3] == '0') // top
                {
                    s_add_top(sl,elbuf,0);
                }
                else if (str[3] == '1') // bot
                {
                    s_add_bot(sl,elbuf,0);
                }
            } else { // right
                if (str[3] == '0') //top
                {
                    s_add_top(sr,elbuf,0);
                }
                else if (str[3] == '1') //bot
                {
                    s_add_bot(sr,elbuf,0);
                }
            }
        }

    s_read_and_free(sl);
    s_read_and_free(sr);
    return 0;
}