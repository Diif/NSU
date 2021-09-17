//
// Created by kiwul on 5/18/2021.
//
#include "../Headers/general.h"

void error_message(int code){
    FILE* log = fopen("log.txt", "w");
    switch (code) {
        case 1: fprintf(log,"Incorrect flag."); break;
        case 2: fprintf(log,"Incorrect archive extension."); break;
        case 3: fprintf(log,"Incorrect command."); break;
        case 4: fprintf(log,"File does not exists."); break;
        case 5: fprintf(log,"File is empty."); break;
        case 6: fprintf(log,"File was corrupted."); break;
        default: fprintf(log,"Unknown error.");
    }
    fclose(log);
    exit(EXIT_FAILURE);
}