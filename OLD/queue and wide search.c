#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// структура "человека".
typedef struct friend_s{
    char* name;// имя
    int chk;// проверялся ли человек ранее
    int seller;// является ли он продавцом
    int fAmt;// сколько у него друзей
    int* friends;// здесь хранятся ключи его друзей, полученные хеш-функцией
}fnd;
int hashFunc(char* name){
    return ((int)name[0])-'a';//не, ну а че вы думали, я буду писать хеш-функцию ради этого? Работает и норм.
}
typedef struct queue_s{// структура очереди
    char* qu[100];// хранит строки, по дефолту длина 11 знаков
    int fst;// первый эл-т очереди
    int last;// последний
    int amt;// их кол-во, чтобы знать, когда очередь пуста/заполнена, т.к. очередь цикличная
}queue;
void Qinit(queue* q){
    q->fst = 0;
    q->last = 0;
    q->amt = 0;
    for (int i = 0; i < 100; ++i) {
        q->qu[i] = (char*)malloc(sizeof(char)*11);// стандартный размер 11 символов
        (q->qu[i])[0] = '\0';
    }
    return;
}
int isEmpty(queue* q){
    return !(q->amt);
}
void Qadd(char* str, queue* q){
    if(q->amt >= 100){
        printf("Queue is full!\n");
        return;
    }
    int len = strlen(str);
    if (isEmpty(q))// для первого элемента очереди
    {
        q->amt++;
        if(len > 10){ // если длина более 11 символов (включая нужный под нулевой)
            char* buf = (char*)malloc(sizeof(char)*(strlen(str)+1));
            strcpy(buf,str);
            free(q->qu[q->last]);// утечки памяти не будет
            q->qu[q->last] = buf;
            return;
        }
        strcpy(q->qu[q->last], str);// если строка помещается
        return;
    }// если у нас очередь не пустая
    q->amt++;
    if(q->last < 100) //т.к. очередь циклична, то последний элемент может быть на 1, а первый - на 99, например.
    q->last++;
    else
        q->last = 0;
    if(len > 10){
        char* buf = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(buf,str);
        free(q->qu[q->last]);
        q->qu[q->last] = buf;
        return;
    }
    strcpy(q->qu[q->last], str);
    return;
}
char* Qremove(queue* q){
    if(isEmpty(q)){
        printf("Queue is empty!\n");
        return NULL;
    }
    int qfst = q->fst;
    if(q->fst < 99)//опять-таки из-за цикличности очереди
        if(q->fst != q->last)// если удаляется последний элемент, то сдвиг сломает очередь
        q->fst++;
    else
        q->fst = 0;
    q->amt--;// по факту удаления нет, но функции не смогут получить доступ к лишнему
    return q->qu[qfst];//возвращаем первый элемент очереди, конечно.
}
void readQueue(queue* q){//просто читает очередь
    int stp = 0;
    for (int i = q->fst; stp <= q->amt; ++i, ++stp) {
        if(i > 99)
            i = 0;
        printf("%s\n", q->qu[i]);
    }
    return;
}
void startInit(char* name, int fAmt, fnd* mas){
    fnd* person = &(mas[hashFunc(name)]);
    person->name = (char*)malloc(sizeof(char)*strlen(name));
    strcpy(person->name,name);
    person->chk = 0;
    person->seller = 0;
    person->fAmt = fAmt;
    int* buf;
    if(fAmt)
    buf = (int*)malloc(sizeof(int)*fAmt);
    else
        buf = NULL;
    person->friends = buf;
    return;
}
int main() {
    freopen(PATH"/input.txt", "r",stdin);
    freopen(PATH"/output.txt", "w",stdout);


    fnd mas[100];

    startInit("you",3,mas);
    (mas[hashFunc("you")].friends)[0] = hashFunc("alice");
    (mas[hashFunc("you")].friends)[1] = hashFunc("bob");
    (mas[hashFunc("you")].friends)[2] = hashFunc("kler");

    startInit("alice",1,mas);
    (mas[hashFunc("alice")].friends)[0] = hashFunc("peggi");

    startInit("bob",2,mas);
    (mas[hashFunc("bob")].friends)[0] = hashFunc("peggi");
    (mas[hashFunc("bob")].friends)[1] = hashFunc("mudge");

    startInit("mudge",0,mas);

    startInit("peggi",0,mas);

    startInit("kler",2,mas);
    (mas[hashFunc("kler")].friends)[0] = hashFunc("tom");
    (mas[hashFunc("kler")].friends)[1] = hashFunc("jon");

    startInit("tom",0,mas);

    startInit("jon",0,mas);

    mas[hashFunc("jon")].seller = 1;


    queue* q = (queue*)malloc(sizeof(struct queue_s));
    Qinit(q);
    Qadd("you",q);
    while(!isEmpty(q)){//пока очередь не пустая
        fnd* buf = &(mas[hashFunc(Qremove(q))]);
        if(buf->chk == 1)//проверка на дубликаты
            continue;
        if(buf->seller == 1){//мы ведь продавца ищем
            printf("The seller is: %s!\n", buf->name);
            break;
        }
        for (int i = 0; i < buf->fAmt; ++i) {// добавляем друзей друзей в очередь
            Qadd(mas[(buf->friends)[i]].name,q);
        }
        buf->chk = 1;//более нам этого человека проверять не нужно
        printf("%s is not a seller!\n", buf->name);
    }
    return 0;
}
