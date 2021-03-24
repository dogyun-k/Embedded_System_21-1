#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t{
    struct Node_t *left;
    int data;
    struct Node_t *right;
}Node_t;

typedef struct Tree {
    Node_t *root;    //맨 앞 노드(가장 최근에 생성한 노드)
}Tree;

void InitTree(Tree* tree){
    tree->root == NULL;
}

int IsEmpty_t(Tree* tree){
    return tree->root == NULL;
}

void insert(Tree* tree, int data){

    Node_t* new = (Node_t*)malloc(sizeof(Node_t));
    new->data = data;
    new->right = NULL;
    new->left = NULL;

    printf("%d\n", data);

    if(IsEmpty_t(tree) == 0){
        tree->root = new;
        return;
    }
    
    Node_t* cur = tree->root;
    while(1){

        if(cur->data < data){
            if(cur->right == NULL){
                cur->right = new;
                return;
            }
            else{
                cur = cur->right;
            }
        }
        else{
            if(cur->left == NULL){
                cur->left = new;
                return;
            }
            else{
                cur = cur->left;
            }
        }

    }//end while

}