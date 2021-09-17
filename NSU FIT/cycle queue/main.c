#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


typedef struct queue{
    int* mas;
    int size;
    int amt;
    int fst;
    int last;
}queue_s;

void q_init(queue_s* q, int size){
    q->mas = (int*)malloc(sizeof(int)*size);
    q->size = size;
    q->amt = 0;
    q->fst = 0;
    q->last = 0;
}

int q_is_empty(queue_s* q){
    return !(q->amt);
}

int q_is_full(queue_s* q){
    if (q->amt >= q->size)
        return 1;
    return 0;
}

int q_add(queue_s* q, int data){
    if (q_is_full(q))
        return 0;
    if (q->amt == 0){ //first element correct initialization
        q->fst = q->last; // stabilization
        q->amt++;
        q->mas[q->last] = data;
        return 1;
    }
    q->amt++;
    if(q->last == (q->size)-1){ // end of cycle check
        q->last = 0;
    }else {
        q->last++;
    }
    q->mas[q->last] = data;
    return 1;
}

int q_remove(queue_s* q){
    if (q_is_empty(q)){
        return 10001;
    }
    int buf = q->mas[q->fst];
    if (q->fst == (q->size)-1){ //end of cycle check
        q->fst = 0;
    } else{
        q->fst++;
    }
    q->amt--;
    return buf;
}

//int amt = 0; // what ???

int main() {
    freopen(PATH"/input.txt", "r",stdin);
    freopen(PATH"/output.txt","w",stdout);
    queue_s* q;
    q = (queue_s*)malloc(sizeof(queue_s));
    int n,m;

    scanf("%d%d", &n,&m);
    q_init(q,n);


    for(; m > 0; m--){
        int op, buf, qcheck;

        scanf("%d", &op);

        if(op > 0){
            while(op > 0){
                scanf("%d", &buf);
                qcheck = q_add(q,buf);
                op--;
                if (!qcheck){
                    printf("Memory overflow\n");
                    while(op > 0){
                        scanf("%d", &buf);
                        op--;
                    }
                }
            }
        } else if (op < 0){
            long long sum = 0;
            int amt = 0;
            op = op*(-1);
            while (op > 0){
                buf = q_remove(q);
                if (buf != 10001) {
                    sum = sum + buf;
                    op--;
                    amt++;
                    if (op == 0){
                        sum = sum / (long long) (amt);
                        printf("%lld\n", sum);
                    }
                    continue;
                } else{
                    if((amt) != 0) {
                        sum = sum/(long long)(amt);
                        printf("%lld\n", sum);
                    }
                    printf("%s", "Empty queue\n");
                    break;
                }
            }
        }
    }
    return 0;
}
