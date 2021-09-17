#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int greetings(FILE** );
int** generate_mas(int, FILE*);
void free_mas(int**, int);
int start_from_small(const void *arg1, const void *arg2);
int start_from_big(const void *arg1, const void *arg2);

//can't work fast
//uses pseudo-random to increase speed and reduce memory usage
int main(){
    FILE* out = NULL;
    int num;
    int** big_mas;

    srand(time(NULL));

    num = greetings(&out);

    printf("\n\tWait a bit...\n");

    big_mas = generate_mas(num, out);

    printf("\t... And It's done!\n");

    free_mas(big_mas, num);
    free(big_mas);
    getchar();
    return 0;


}

int greetings(FILE** out) {
    int input_number, is_correct = 0; // unsigned maybe? It is long enough.
    char buf[11] = {0}; //11 symbols <=> 2 147 483 647 + '\0'
    char select_output = '\0';

    printf("\tHey bro, nice number, can you show it?\n");
    while (!is_correct) {

        scanf("%11s", buf);
        fflush(stdin); // clean stream
        input_number = strtol(buf,NULL,10); // float -> int

        if (input_number <= 0 || input_number > 1073741823) {
                printf("\tOh, It's nice, but I prefer something... more natural... (0 < natural number <= 1 073 741 823)\n");
            } else {
            is_correct = 1;
        }

    }

    is_correct = 0;

    printf("\n\tShould I create file \"output.txt\" for results? (y/n)\n");

    while (!is_correct) {

        scanf("%c", &select_output);
        fflush(stdin); // clean stream

        if (select_output == 'n') {
            *out = stdout;
            is_correct = 1;
        } else if (select_output == 'y') {
            *out = fopen("output.txt", "w");
            is_correct = 1;
        } else {
            printf("\n\tPlease, use symbols \"y\" - yes, either \"n\" - no.\n");
        }

    }
    return input_number;
}

int random_generator(int max, char* used) {

    if (used) {

        int try_small = 0, s_limit = RAND_MAX * 0.7; //uses to save memory and increase speed
        int try_medium = 0, m_limit = (RAND_MAX * RAND_MAX * 0.7) - s_limit;
        int res = (((rand() + 1) % max) + 1);

        while (1) {

            if (used[res] == '\0') {
                used[res] = 1;
                try_small++;
                return res;
            } else if (try_small < s_limit) {
                while (1) {
                    res = (((rand() + 1) % max) + 1);
                    if (used[res] == '\0') {
                        used[res] = 1;
                        try_small++;
                        return res;
                    }
                }
            }

            if (used[res] == 1) {
                res = (((rand() * rand() + 1) % max) + 1); //RAND_MAX can't be > 32767
            }

            if (used[res] == '\0') {
                used[res] = 1;
                return res;
            } else if (try_medium < m_limit) {
                while (1) {
                    res = (((rand() * rand() + 1) % max) + 1);
                    if (used[res] == '\0') {
                        used[res] = 1;
                        try_medium++;
                        return res;
                    }
                }
            }

            if (used[res] == 1) {
                res = ((((long long) rand() * rand() * rand() + 1) % max) + 1);
                used[res] = 1;
            }

            if (used[res] == '\0') {
                used[res] = 1;
                return res;
            }
        }
    } else {
        return rand(); //rand num  from [0;RAND_MAX]
    }
}



int** generate_mas(int num, FILE* out){
    int max = num*2; //random size of mas can't be > num*2 to reduce memore\CPU use
    char* used_numbers = (char*)malloc(sizeof(char)*(max+1));// to prevent the same size

    for(int i = 0; i<=max;i++) {
        used_numbers[i] = '\0';
    }

    int** big_mas = (int**)malloc(sizeof(int*)*num); //mas of mas init

    for(int i = 0; i < num; i++){
        int amt = random_generator(max, used_numbers); // mas size

        big_mas[i] = (int*)malloc(sizeof(int)*amt);
        fprintf(out, "\tMassive #%d:\n\tSize: %d\n", i+1, amt);

        for(int j = 0; j < amt; j++){
            (big_mas[i])[j] = random_generator(1, NULL); // put random numbers from [0; RAND_MAX]
        }

        if((i+1)%2 == 0){
            qsort((big_mas[i]), amt, sizeof(int),start_from_small); //sort
        } else {
            qsort((big_mas[i]), amt, sizeof(int),start_from_big);
        }
        for(int j = 0; j < amt; j++) {
            fprintf(out, "%d ", (big_mas[i])[j]);
        }
        fprintf(out, "\n");
    }
    free(used_numbers);
    return big_mas;
}

void free_mas(int** mas, int size){
    size--;
    while(size >= 0){
        free(mas[size]);
        size--;
    }
}

int start_from_small(const void *arg1, const void *arg2){
    return ( (*(int*)arg1) - (*(int*)arg2));
}
int start_from_big(const void *arg1, const void *arg2){
    return ( (*(int*)arg2) - (*(int*)arg1));
}