#include <stdio.h>
#include <malloc.h>

int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

int main(){
   FILE* in, *out;
    in = fopen(PATH"/input.txt", "r");
    out = fopen(PATH"/output.txt", "w");

    int amt, wgh;
    int** mas;

    fscanf(in,"%d%d",&amt,&wgh);
    amt = amt+2;
    wgh = wgh+3;
    mas = (int**)malloc(sizeof(int*)*amt);

    //строим матрицу размером amt+1 на wgh+2 и заполняем весом/ценой/нолями.
    for(int i = 0; i < amt;i++){
        mas[i] = (int*)malloc(sizeof(int)*wgh);
        for (int j = 0; j < wgh; ++j) {
            if(i == 0){
                mas[i][j] = j-2;
            } else {
                if(j == 0 && i == 1){
                    mas[i][j] = 0;
                    mas[i][j+1] = 0;
                    j++;
                    continue;
                }else if(j == 0){
                    fscanf(in,"%d%d", &(mas[i][j]),&(mas[i][j+1]));
                    j = j+1;
                    continue;
                }
                mas[i][j] = 0;
            }
        }
    }
/*
    //TODO DEBUG
    fprintf(out,"MATRIX: \n");
    for(int i = 0; i < amt; i++){
        for (int j = 0; j < wgh; ++j) {
            if(j==0){
                fprintf(out,"%d|%d| ",mas[i][j],mas[i][j+1]);
                j++;
            } else{
                fprintf(out,"%d ",mas[i][j]);
            }
        }
        fprintf(out,"\n");
    }
    fprintf(out,"\n");
    //TODO DEBUG
*/

    for(int i = 2; i<amt;i++) {
        int weight = mas[i][0];
        int val = mas[i][1];

        for (int j = 2; j < wgh; j++) {
            if (mas[0][j] < weight) {
                mas[i][j] = mas[i - 1][j];
            } else {
                if (mas[i - 1][j - weight] + val > mas[i - 1][j]) {
                    mas[i][j] = mas[i - 1][j - weight] + val;
                } else {
                    mas[i][j] = mas[i - 1][j];
                }
            }
        }
    }
/*
    //TODO DEBUG
    fprintf(out,"MATRIX: \n");
    for(int i = 0; i < amt; i++){
        for (int j = 0; j < wgh; ++j) {
            if(j==0){
                fprintf(out,"%d|%d| ",mas[i][j],mas[i][j+1]);
                j++;
            } else{
                fprintf(out,"%d ",mas[i][j]);
            }
        }
        fprintf(out,"\n");
    }
    fprintf(out,"\n");
    //TODO DEBUG
*/
   int final_weight = 0,
        final_amt = 0,
        final_val = mas[amt-1][wgh-1];
    for(int i = amt-1, j = wgh-1; i > 0 && j  > 1 && mas[i][j] != 0;) {
        if (mas[i][j] == mas[i - 1][j]) {
            i--;
            continue;
        } else {
          //  fprintf(out, "%d ", i);
            final_weight+= mas[i][0];
            final_amt++;
            j = j - mas[i][0];
            i--;
        }
    }
    fprintf(out, "%d %d %d\n", final_amt, final_weight, final_val );

    for(int i = amt-1, j = wgh-1; i > 0 && j  > 1 && mas[i][j] != 0;) {
        if (mas[i][j] == mas[i - 1][j]) {
            i--;
            continue;
        } else {
            fprintf(out, "%d ", i-1);
            j = j - mas[i][0];
            i--;
        }
    }
    return 0;
}