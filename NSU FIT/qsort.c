#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void RecQsort(int left, int right, int* mas){
    int pivot = mas[(right+left)/2];
    int l = left, r = right;
    while(l < r){
        while(mas[l] < pivot)
            l++;
        while(mas[r] > pivot)
            r--;
        if(l <= r) {
            int buf = mas[l];
            mas[l] = mas[r];
            mas[r] = buf;
            r--;
            l++;
        }
    }

    if(r > left)
        RecQsort(left, r, mas);
    if (l < right)
        RecQsort(l, right, mas);
}
void printMas(int* mas, int n){
    for (int i = 0; i < n; ++i) {
        printf("%d ", mas[i]);
    }
}
int main() {
    freopen(PATH"/input.txt", "r",stdin);
    freopen(PATH"/output.txt", "w",stdout);
    int n;
    scanf("%d",&n);
    int* mas = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &(mas[i]));
    }
    RecQsort(0, n - 1, mas);
    printMas(mas,n);
    return 0;
}
