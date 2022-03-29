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
void sift_down(int ind, heap_s* h){
    if (ind == (h->amt) || ind > h->amt){
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
int main() {

    freopen(PATH"/input.txt", "r", stdin);
    freopen(PATH"/output.txt", "w", stdout);

    int n, buf;

    scanf("%d", &n);
    heap_s* h = h_init(n);
    h->amt = n;
    int* test = (int*)malloc(sizeof(int)*n);

    for(int i = 1; i<=n; i++){
        scanf("%d", &buf);
        h->mas[i] = buf;
    }

    for(int i = 0; i<n; i++){
        test[i] = h->mas[i+1];
    }

    for(int i = n/2; i>=1;i--){
        sift_down(i,h);
    }

        for (int i = n; i >= 2; i--) {
            swap(1, i, h);
            h->amt--;
            sift_down(1, h);
        }

    for(int i = n; i >=1; i--){
        printf("%d ", h->mas[i]);
    }
    printf("\n");
return 0;
}