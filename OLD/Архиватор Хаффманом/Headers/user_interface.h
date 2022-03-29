//
// Created by kiwul on 5/18/2021.
//

#ifndef TEST_USER_INTERFACE_H
#define TEST_USER_INTERFACE_H
#include <stdio.h>
#include <string.h>
#include <malloc.h>
char** get_args(int* argc);
int get_word_len(char* str);
char get_command(const char* flag);
void check_arc_ext(char* arc);
void print_commands();
void print_greetings();
void UI(int *argc, char** args);
#endif //TEST_USER_INTERFACE_H
