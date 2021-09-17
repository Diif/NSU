#include <stdio.h>

int main() {
    freopen(PATH"/input.txt", "r",stdin);

    int buf;

    /* line to coll
    freopen(PATH"/ord1output.txt","w",stdout);
    scanf("%d",&buf);
    printf("%d ", buf);
    scanf("%d",&buf);
    printf("%d\n", buf);

    while(scanf("%d",&buf) > 0)
        printf("%d\n", buf);*/


    freopen(PATH"/ordoutput.txt","w",stdout);
    scanf("%d",&buf);
    int max = buf;
    printf("BUF SIZE: %d\n", buf);
    scanf("%d",&buf);
    int line = 1;
    int flag = 1;
    while(scanf("%d",&buf) > 0) {
        int amt = 0;
        line++;
        int bla;
        int amtsum = 0;
        int sum = 0;
        if (buf > 0) {
            printf("Operation: %d in line: %d\n", buf, line);
            while (buf > 0) {
                scanf("%d", &bla);
                if (line == 256 )
                    printf("\nMY LINE: %d\n", bla);
                if(line <= 279 && line >=256 ){
                    if(flag) {
                        printf("\nFST IS: %d\n", bla);
                        flag--;
                    }
                    amtsum++;
                    sum = sum + bla;
                }
                if (amtsum == 24 && line == 281){
                        printf("TOTAL SUM: %d AND ANSWER: %d\n", sum, sum/amtsum);
                }
                amt++;
                line++;
                buf--;
            }
        } else {
            printf("Operation: %d in line: %d\n", buf, line);
            buf = buf * (-1);
            while (buf > 0) {
                amt--;
                buf--;
                if(buf == 0)
                    break;
            }
        }
    }

/*
    freopen(PATH"/sum.txt","w",stdout);
    int sum = 0;
    int amt = 0;
    while (scanf("%d", &buf) > 0)
    {
        amt++;
        sum = sum + buf;
    }
    printf("%d", sum/amt);
    return 0;*/
}
