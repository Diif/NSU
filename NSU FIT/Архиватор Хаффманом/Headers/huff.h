//
// Created by kiwul on 5/19/2021.
//

#ifndef TEST_HUFF_H
#define TEST_HUFF_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "general.h"
typedef unsigned char uchar;
typedef unsigned long long bitword;

typedef struct tree_s{
    uchar letter;
    int freq;
    struct tree_s *left;
    struct tree_s *right;
}tree;

typedef struct code_s{
    long long bits[4];
    char levels;//можно из count считать отдельно, но понятнее так
    int count;
}Code;

int get_freq_and_num_chars(int* freq, FILE* in);
tree* create_node(int freq, uchar letter, tree* left, tree* right);
int compare(const void* p1, const void* p2);
tree* create_tree(int num_of_chars, int *freq);
void create_code(Code *res, tree* root, bitword *code_buf, uchar code_level, int height);
void set_bit(int bit, bitword *word, int ind);
void encode(FILE* in, FILE* out, char* file_name);

int calc_tree_size(tree* root);
void calc_size(i64 *o_total_size_bites, const int *freq, Code *code, tree* root);
i64 get_org_size_bytes(FILE* input);
char calc_compression(i64 org, i64 total_size);

typedef struct {
    uchar Byte; // какой код в этом байте
    int BitCount; //сколько осталось бит
    FILE* File;
} BitWriter;

void write_file_title(FILE* out, char* name, i64 size,char compression,BitWriter *bw,tree* root);
void write_bit(int bit, BitWriter* BW);
void close_writer(BitWriter *BW);
void write_bits(bitword code, int code_len,BitWriter* BW);

typedef struct {
    uchar Byte; // какой код в этом байте
    bitword BitCount; // сколько ещё не прочитано
    FILE* File;
} BitReader;

void decode(FILE* in);
char* get_name(FILE* in);
void get_file_info(char** name,i64 *size, char *compression, FILE* in);
void read_coded_char(FILE* in, FILE* out, tree* root, BitReader *br, i64 *oTotal_size_bites, uchar was_read);
tree* ReadTree(BitReader* br);
uchar read_8bits(BitReader* BR);
int read_bit(BitReader* BR);
#endif //TEST_HUFF_H
