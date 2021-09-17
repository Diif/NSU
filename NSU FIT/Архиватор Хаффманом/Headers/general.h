//
// Created by kiwul on 5/18/2021.
//

#ifndef TEST_GENERAL_H
#define TEST_GENERAL_H
#define ERROR_FLAG 1
#define ERROR_EXT 2
#define ERROR_COMMAND 3
#define ERROR_N_EXISTS 4
#define ERROR_EMPTY 5
#define ERROR_CORRUPTED 6
#define ERROR_UNKNOWN 100
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long i64;
void error_message(int code);

#endif //TEST_GENERAL_H
