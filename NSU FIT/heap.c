#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
    int* mas;
    int size;
    int amt;
}heap_s;


heap_s* h_init(int size){
    heap_s* h = (heap_s*)malloc(sizeof(heap_s));
    h->size = size;
    h->amt = 0;
    h->mas = (int*)malloc(sizeof(int)*(size+1));
return h;
}
int h_is_empty(heap_s* h){
    return !(h->amt);
}
int parent(int ind, heap_s* h){
    if (ind % 2 == 0) {
            return (ind) / 2;
        }
    return (ind-1) / 2;
}

void swap(int ind1, int ind2, heap_s* h){
    int buf = h->mas[ind1];
    h->mas[ind1] = h->mas[ind2];
    h->mas[ind2] = buf;
}

int left(int ind, heap_s* h){
    if(ind*2 <= h->amt) {//TODO it's not enough
        return ind * 2;
    }
    return -1;
}

int right(int ind, heap_s* h){
    if((ind*2)+1 <= h->amt) {//TODO it's not enough
        return (ind * 2)+1;
    }
    return -1;
}

void sift_up(int ind, heap_s* h){
    if (ind == 1){
        return;
    }

    if( h->mas[ind] < h->mas[parent(ind, h)]) {
        swap(ind, parent(ind, h), h);
        sift_up(parent(ind, h), h);
    }
}

void sift_down(int ind, heap_s* h){
    if (ind == (h->amt)){
        return;
    }

    int min;
    int num = h->mas[ind];

    int ileft = left(ind,h);
    int iright = right(ind,h);

    if (ileft > 0 && h->mas[ileft] < num){
        min = ileft;
    } else {
        min = ind;
    }
    if(iright > 0 && h->mas[iright] < h->mas[min]){
        min = iright;
    }
    if (min != ind){
        swap(min,ind,h);
        sift_down(min,h);
    }
}

int pop(heap_s* h) {//TODO add "cant find" error
    if (h_is_empty(h)){
        return 100001;
    }
    int buf = h->mas[1];
    h->mas[1] = h->mas[(h->amt)];
    h->amt--;
    sift_down(1,h);
    return buf;
}

int push(heap_s* h, int data){//TODO add overflow check
    h->amt++;
    h->mas[h->amt] = data;
    sift_up((h->amt),h);
}

int main() {

    freopen(PATH"/input.txt", "r", stdin);
    freopen(PATH"/output.txt", "w", stdout);
    printf("");
    int n, buf;
    char op[5] = {0};

    scanf("%d", &n);
    heap_s* h = h_init(n);


    for(int i = 1; i <= n; i++){
        scanf("%s", op);
        if(op[1] == 'u'){
            scanf("%d", &buf);
            push(h,buf);
        } else if(op[1] == 'o'){
            buf = pop(h);
            if(buf == 100001){
                printf("Heap is empty\n");
            } else {
                printf("%d\n", buf);
            }
        }
    }
    printf("\n");
return 0;
}