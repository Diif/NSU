#include <stdio.h>
#include <malloc.h>
#include <string.h>

// FIFO-LIFO
typedef struct list_stack{
    int* mas;
    int top;
    int bot;
    int amt;
    int size;
}stack_s;

int s_is_empty(stack_s* st){
    return !st->amt;
}

void s_add_bot(stack_s* st, int el){
    if (st->bot == 0  && !s_is_empty(st)){ //cycle check
        st->bot = st->size;
    }
    if(!(s_is_empty(st))) { // empty check
        st->bot--;
    }
    st->mas[st->bot] = el;
    st->amt++;
}

int s_rem_bot(stack_s* st){
    if (s_is_empty(st)){ //do nothing
        return 0;
    }
       int buf = st->mas[st->bot];
       st->amt--;
       st->bot++;
    if (st->bot == st->size) { //cycle check
        st->bot = 0;
    }
    if (st->amt == 0) {// stabilization
           st->bot = st->top;
    }
       return buf;
}

void s_add_top(stack_s* st, int el){
    if (st->top == st->size-1 && !s_is_empty(st)){ //cycle check
        st->top = -1;
    }
    if(!(s_is_empty(st))){
        st->top++;
    }
    st->mas[st->top] = el;
    st->amt++;
}

int s_rem_top(stack_s* st){
    if(s_is_empty(st)){
        return 0;
    }
    int buf = st->mas[st->top];
    st->top--;
    if (st->top == -1) //cycle check
    {
        st->top = (st->size-1);
    }
    st->amt--;
    if(st->amt == 0){
        st->top = st->bot; //stabilization
    }
    return buf;
}

void s_read_and_free(stack_s* st){ // after rebuilding has no free
    if(s_is_empty(st)){
        printf("%d\n", st->amt);
        return;
    }
    printf("%d ", st->amt);
    for(int count = st->amt; count > 0; count--){
        printf("%d ", s_rem_top(st));
    }
    printf("\n");
}

void s_init(stack_s* st, int n){//init for 2n elements
    int flag = 0;
    if (n < 0){
        flag++;
        n= n*(-1);
    }
    st->mas = (int*)malloc(sizeof(int)*2*n);
    st->size = 2*n;
    st->amt = 0;
    st->top = 0;
    st->bot = 0;
    if(!flag) {
        while (n > 0) {
            s_add_top(st, n);
            n--;
        }
    } else {
        while (n > 0) {
            s_add_top(st, -n);
            n--;
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
    if ((c >= '0' && c<= '9') || (c<='F' && c>='A' ))//for tests
        return 0;
    return 1;
}

int s_top(stack_s* st){//top element for debug
    return st->mas[st->top];
}

void s_watch(stack_s* st){// debug fnct
    if(s_is_empty(st)){
        printf("%d\n", st->amt);
        return;
    }
    printf("%d ", st->amt);
    int pos = st->top;
    for(int count = st->amt; count > 0; count--){
        printf("%d ", st->mas[pos]);
        pos--;
        if (pos == -1)
        {
            pos = (st->size-1);
        }
    }
    printf("\n");
}

int main() {
    freopen(PATH"/input.txt", "r", stdin);
    freopen(PATH"/output.txt", "w", stdout);

    stack_s* sl = (stack_s*)malloc(sizeof(stack_s));
    stack_s* sr = (stack_s*)malloc(sizeof(stack_s));
    int n,m,flag;
    char buf;
    char str[5];
    int valbuf;
    scanf("%d%d", &n,&m);

    s_init(sl,n);
    s_init(sr,-n);


    for(; m > 0; m--) {
        scanf("%c", &buf);
        if (buf == '\n') {// exception for \n
            m++;
            continue;
        }
        if (skip(buf)) {//skip iteration because of useless commands
            continue;
        }
        strcpy(str, get_op(buf));
        //from left either right?
        if (str[0] == '0') { // left!
            //from bot either top?
            if (str[1] == '0') // top
            {
                valbuf = s_rem_top(sl);
                if (!valbuf)
                    continue;
            } else if (str[1] == '1') // bot
            {
                valbuf = s_rem_bot(sl);
                if (!valbuf)
                    continue;
            }
        } else { // right
            if (str[1] == '0') //top
            {
                valbuf = s_rem_top(sr);
                if (!valbuf)
                    continue;
            } else if (str[1] == '1') //bot
            {
                valbuf = s_rem_bot(sr);
                if (!valbuf)
                    continue;
            }
        }
        //to left either right?
        if (str[2] == '0') { // left!
            //to bot either top?
            if (str[3] == '0') // top
            {
                s_add_top(sl, valbuf);
            } else if (str[3] == '1') // bot
            {
                s_add_bot(sl, valbuf);
            }
        } else { // right
            if (str[3] == '0') //top
            {
                s_add_top(sr, valbuf);
            } else if (str[3] == '1') //bot
            {
                s_add_bot(sr, valbuf);
            }
        }
        /*  {//TODO DEBUG BLOCK
              printf("AFTER OP %d WE HAVE SR:", m);
              s_watch(sr);
              printf("AFTER OP %d WE HAVE SL:", m);
              s_watch(sl);
              if(m == 740 || m== 731 || m== 730 || m == 729){
                  printf("INF ABOUT SR: amount %d | top %d | bot %d |", sr->amt, sr->top,sr->bot);
                  printf("\n");
                  printf("OPERATION IS: %s", str);
                  printf("\n");
              }
              printf("\n");

          }*/
    }

    s_read_and_free(sl);
    s_read_and_free(sr);
    return 0;
}