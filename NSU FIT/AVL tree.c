#include <stdio.h>
#include <malloc.h>

typedef struct tree_s{
    int key;
    unsigned char height;
    struct tree_s* left;
    struct tree_s* right;
}tree;

unsigned char height(tree* root){
    return root?root->height:0;
}

void upd_height(tree* root){
    unsigned char hl = height(root->left);
    unsigned char hr = height(root->right);

    root->height = (hl<=hr?hr:hl)+1;
}

tree* rotate_left(tree* node){
    tree* rgh_node = node->right;
    node->right = rgh_node->left;
    rgh_node->left = node;
    upd_height(node);
    upd_height(rgh_node);
    return rgh_node;
}

tree* rotate_right(tree* node){
    tree* left_node = node->left;
    node->left = left_node->right;
    left_node->right = node;
    upd_height(node);
    upd_height(left_node);
    return left_node;
}

int bfactor(tree* root)
{
    return height(root->right)-height(root->left);
}

tree* balance(tree* root){
    upd_height(root);
    int bfact = bfactor(root);
    if(bfact == 2){
        if(bfactor(root->right) < 0){
            root->right = rotate_right(root->right);
        }
        return rotate_left(root);

    } else if(bfact == -2){
        if(bfactor(root->left) > 0){
            root->left = rotate_left(root->left);
        }
        return rotate_right(root);

    }
    return root;
}

tree* create_node(int key){
    tree* node = (tree*)malloc(sizeof(tree));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

tree* insert(tree* root, int key){
    if(!root){
        return create_node(key);
    } else if(key < root->key){
        root->left = insert(root->left,key);
    } else{ //if(key >= root->key){
        root->right = insert(root->right, key);
    }
    return balance(root);
}

tree* find_min(tree* root){//отправлять только правого сына!
    return root->left?find_min(root->left):root;
}

tree* remove_min(tree* root){
    if(!root->left){
        return root->right;
    }
    root->left = remove_min(root->left);
    return balance(root);
}

tree* remove_by_key(tree* root, int key){
    if(!root){
        return NULL;
    }

    if(key < root->key){
        root->left = remove_by_key(root->left, key);
    }else if(key > root->key){
        root->right = remove_by_key(root->right,key);
    }else{
        tree* left = root->left;
        tree* rght = root->right;
        free(root);
        if(rght == NULL){
            return left;
        }
        tree* min = find_min(rght);
        min->right = remove_min(rght);
        min->left = left;
        return balance(min);
    }
    return balance(root);
}

void print_val(tree* root, FILE* out){
    if(root) {
        if (root->left) {
            print_val(root->left, out);
        }
        fwrite(&root->key,sizeof(int),1,out);
        if (root->right) {
            print_val(root->right, out);
        }
    }
}

int main(){
    FILE* in, *out;

    in = fopen(PATH"/input.bin", "rb");
    out =fopen(PATH"/output.bin","wb");

    int buf, n;
    tree* root = NULL;

    fread(&n,sizeof(int),1,in);

    for(int i =0; i<n;i++){
        fread(&buf,sizeof(int),1,in);
        root = insert(root,buf);
    }

    print_val(root,out);
    return 0;
}