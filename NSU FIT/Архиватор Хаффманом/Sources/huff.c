//
// Created by kiwul on 5/19/2021.
//
#include "../Headers/huff.h"

int get_freq_and_num_chars(int* freq, FILE* in){
    if(!in){
        error_message(ERROR_N_EXISTS);
    }
    int c = 0;
    int counter = 0;
    while(fread(&c,1,1,in)){
        if(freq[c] == 0){
            counter++;
        }
        freq[c]++;
    }
    if(counter == 0){
        error_message(ERROR_EMPTY);
    }
    return counter;
}

tree* create_node(int freq, uchar letter, tree* left, tree* right){
    tree* node = (tree*)malloc(sizeof(tree));
    node->right = right;
    node->left = left;
    node->freq = freq;
    node->letter = letter;
    return node;
}

int compare(const void* p1, const void* p2) {
    int arg1 = ((*(tree**)p1)->freq);
    int arg2 = ((*(tree**)p2)->freq);
    return arg2 - arg1;
}


tree* create_tree(int num_of_chars, int *freq){


    tree** nodes = (tree**)malloc(sizeof(tree*)*num_of_chars);


    //строим листья
    for (int i = 0, j = 0; j < num_of_chars; ++i) {
        if(freq[i] != 0){
            nodes[j] = create_node(freq[i],i, NULL,NULL);
            j++;
        }
    }
    qsort(nodes,num_of_chars, sizeof(tree*),(int (*)(const void*, const void*))compare);
    //строим само дерево

    while (num_of_chars != 1){
        tree* left = nodes[--num_of_chars];
        tree* right = nodes[--num_of_chars];
        int sum_freq = left->freq + right->freq;
        nodes[num_of_chars++] = create_node(sum_freq, 0,left,right);
        qsort(nodes,num_of_chars,sizeof(tree*),compare);
    }

    return nodes[0];
}

void set_bit(int bit, bitword *word, int ind){
    if(bit){
        (*word) |= (1<<ind);
    }else{
        (*word) &= ~(1<<ind);
    }
}

void create_code(Code *res, tree* root, bitword *code_buf, uchar code_level, int height){
    if(root->left && root->right) {//одного сына быть не может, поэтому для проверики на двух можно проверить одного
        if(height % 64 == 0 && height !=0){
            code_level++;
        }
        height++;
        set_bit(0,&(code_buf[code_level]),0);

        if(height%64 != 0) {
            code_buf[code_level] = (code_buf[code_level]) << 1;
        }

        create_code(res,root->left,code_buf,code_level,height);

        if(height%64 != 0) {
            code_buf[code_level] = (code_buf[code_level]) >> 1;
        }
        set_bit(1,&(code_buf[code_level]),0);
        if(height%64 != 0) {
            code_buf[code_level] = (code_buf[code_level]) << 1;
        }

        create_code(res,root->right,code_buf,code_level,height);

        if(height%64 != 0) {
            code_buf[code_level] = (code_buf[code_level]) >> 1;
        }

    }else{
        if(!height){
            height++;//одноузловое дерево
        }
        if(height%64 != 0){
            code_buf[code_level] = (code_buf[code_level]) >> 1;//изначально бит свободен
        }
        for (int i = code_level; i >=0 ; --i) {
            res[root->letter].bits[code_level] = code_buf[code_level];
        }
        res[root->letter].levels = code_level;
        res[root->letter].count = height;
        if(height%64 != 0){
            code_buf[code_level] = (code_buf[code_level]) << 1;//нужо вернуть на место, ибо буфер общий
        }
    }
}

int calc_tree_size(tree* root){
    if(root->left && root->right){
        return calc_tree_size(root->left) + calc_tree_size(root->right) + 1;
    } else{
        return (sizeof(char)*8)+1;
    }
}

void calc_size(i64 *o_total_size_bites, const int *freq, Code *code, tree* root){
    i64 total_size = 0;//считает размер без заголовка, но с деревом!
    for (int i = 0; i < 256; ++i) {
        if(freq[i] != 0){
            total_size += (freq[i]*code[i].count);
        }
    }
    total_size += calc_tree_size(root);
    if(o_total_size_bites) {
        (*o_total_size_bites) = total_size;
    }
}

void write_tree(BitWriter* bw, tree* root) {
    if(!root){
        error_message(ERROR_UNKNOWN);
    }
    if (root->right && root->left) {
        write_bits(1, 1, bw);
        write_tree(bw, root->right);
        write_tree(bw, root->left);
    } else { // 0 and tree->Char
        write_bits(0,1,bw);
        write_bits(root->letter,CHAR_BIT, bw);
    }
}

void write_file_title(FILE* out, char* name, i64 size,char compression, BitWriter *bw,tree* root){
    int len = strlen(name);
    uchar zero = 0;
    fwrite(name,sizeof(char),len,out);//имя
    fwrite(&zero,sizeof(char),1,out);//нолик как окончание имени
    fwrite(&compression,sizeof(char),1,out);//процент сжатия
    fwrite(&size,sizeof(i64),1,out);//размер файла
    write_tree(bw,root);
}

i64 get_org_size_bytes(FILE* in){
    fseek(in,0L,SEEK_END);
    return ftell(in);
}

char calc_compression(i64 org, i64 total_size){
    char res;
    if(org > total_size){
        res = (char)round(((double)total_size / org)*100);
    }else{
        res = (char)-round(((double)org / total_size)*100);
    }
    return res;
}

void close_writer(BitWriter *BW){
    if(BW->BitCount){
        int shift = 8-(BW->BitCount)-1;//т.к. заполнение байта происходит справа налево, то слева образуются
        BW->Byte = (BW->Byte)<<shift;//незанятые биты, которые нужно сдвинуть
        fwrite(&(BW->Byte),sizeof(char),1,BW->File);
    }
    fclose(BW->File);
}

uchar get_bit_by_pos(bitword code, int pos){
    i64 mask = 1;
    int shift = pos;
    if(shift > 0){
        code = code>>shift;
    }
    return (code&mask);
}

void write_bit(int bit, BitWriter* BW){
    FILE* out = BW->File;
    set_bit(bit,&(BW->Byte),0);//TODO если будет некорректо, то пофиксить
    (BW->BitCount)++;//По дефолту считается, что бит не занят был
    if(BW->BitCount == 8){
        fwrite(&(BW->Byte),sizeof(char),1,out);
        BW->BitCount = 0;
        BW->Byte = 0; // для красоты скорее
    }else{
        BW->Byte = (BW->Byte)<<1;
    }

}

void write_bits(bitword code, int code_len,BitWriter* BW){
    int pos = code_len-1;
    i64 buf;
    for (int i = 0; i < code_len; ++i) {
        buf = get_bit_by_pos(code,pos);
        code = code<<1;
        if(buf){
            write_bit(1,BW);
        }else{
            write_bit(0,BW);
        }
    }
}

void write_file(FILE* in,Code *code, BitWriter *BW){
    fseek(in,0,SEEK_SET);
    uchar c;
    char levels;
    int len;
    while (fread(&c,1,1,in)){
        levels = code[c].levels;
        len = code[c].count;
        for (int i = 0; i <= levels; ++i) {
            if(levels > 0){
                write_bits(code[c].bits[i],64,BW);
                len -=64;
            } else{
                write_bits(code[c].bits[i],len,BW);
            }
            if(len < 0 || levels < 0){
                error_message(ERROR_UNKNOWN);
            }
        }
    }
    close_writer(BW);

}

int get_info(int* freq){
    i64 res = 0;
    for (int i = 0; i < 256; ++i) {
        res+=freq[i];
    }
    return res;
}
void encode(FILE* in, FILE* out, char* file_name){
    int level = 0, height = 0, num_of_chars;
    int freq[256] = {0};
    i64 org_size;
    i64 total_size = 0;
    char compression;

    num_of_chars = get_freq_and_num_chars(freq,in);
    i64 ce = get_info(freq);
    tree* root = create_tree(num_of_chars,freq);
    Code code[256];
    bitword code_buf[4];

    for (int i = 0; i < 256; ++i) {//инициализация
        for (int j = 0; j < 4; ++j) {
            code[i].bits[j] = 0;
        }
        code[i].count = 0;
        code[i].levels = 0;
    }

    create_code(code,root,code_buf,level,height);
    calc_size(&total_size,freq,code,root);
    org_size = get_org_size_bytes(in)*8;
    compression = calc_compression(org_size,total_size);

    BitWriter BW;
    BW.File = out;
    BW.BitCount = 0;
    BW.Byte = 0;

    write_file_title(out,file_name,total_size,compression, &BW,root);
    write_file(in,code, &BW);
    fclose(in);
    fclose(out);
}

char* get_name(FILE* in){
    char name[1000];
    for (int i = 0; i < 1000; ++i) {
        fread(&(name[i]),1,1,in);
        if(name[i] == '\0'){
            break;
        }
    }
    int len = strlen(name);
    char* res = (char*)malloc(sizeof(char)*(len+1));
    strcpy(res,name);
    return res;
}


int read_bit(BitReader* BR){
    FILE* in = BR->File;
    if(BR->BitCount == 0){
        if(fread(&(BR->Byte),1,1,in)) {
            BR->BitCount = 8;
        } else {
            error_message(ERROR_CORRUPTED);
        }
    }
    uchar bit = get_bit_by_pos(BR->Byte,7);//По дефолту считается, что бит не пустышка
    BR->BitCount--;
    BR->Byte = (BR->Byte)<<1;
    return bit;
}

uchar read_8bits(BitReader* BR){
    uchar res = 0;
    for (int i = 0; i < 8; ++i) {
        int buf = read_bit(BR);
        res+=buf;
        if(i != 7) {
            res = res << 1;
        }
    }
    return res;
}

tree* ReadTree(BitReader* br) {
    uchar c = 0;
    c = read_bit(br);
    if (c) {
        tree* r = ReadTree(br);
        tree* l = ReadTree(br);
        tree* t = create_node(0,0,l,r);
        return t;
    } else {
        tree* t = create_node(0, read_8bits(br), 0, 0);
        return t;
    }
}

void read_coded_char(FILE* in, FILE* out, tree* root, BitReader *br, i64 *oTotal_size_bites, uchar was_read){
    if(root->right && root->left){
        uchar bit = read_bit(br);
        (*oTotal_size_bites)--;
        if((*oTotal_size_bites) < 0){
            error_message(ERROR_CORRUPTED);
        }
        if(bit){
            read_coded_char(in,out,root->right,br, oTotal_size_bites,1);
        }else{
            read_coded_char(in,out,root->left,br,oTotal_size_bites,1);
        }
    }else{//TODO разобраться с одноузловым деревом
        if(!was_read){
            read_bit(br);
            (*oTotal_size_bites)--;
        }
        fwrite(&(root->letter),1,1,out);
    }
}

void get_file_info(char** name,i64 *size, char *compression, FILE* in){
    (*name)=get_name(in);
    fread(compression,1,1,in);
    fread(size,8,1,in);
}

void decode(FILE* in){
    FILE *out;
    char* name;
    char compression;
    int tree_size;
    i64 size;
    BitReader br;
    br.Byte = 0;
    br.BitCount = 0;
    br.File = in;
    //чтение заголовка
    name = get_name(in);
    out = fopen(name,"wb");
    fread(&compression,1,1,in);
    fread(&size,8,1,in);
    //чтение дерева
    tree* root = ReadTree(&br);
    tree_size = calc_tree_size(root);
    size-=tree_size;
    while(size){
        read_coded_char(in,out,root,&br,&size,0);
    }
    fclose(in);
    fclose(out);
}
