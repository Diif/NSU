#include <stdio.h>
#include "Headers/user_interface.h"
#include "Headers/huff.h"//TODO оставить только интерфейс


int main(int argc,char** argv) {
    print_greetings();
    UI(&argc,argv);
    getc(stdin);
    return 0;
}
