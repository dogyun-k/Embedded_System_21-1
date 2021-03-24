typedef struct Node_t{
    struct Node_t *left;
    int data;
    struct Node_t *right;
}Node_t;

typedef struct Tree {
    Node_t *root;    //맨 앞 노드(가장 최근에 생성한 노드)
}Tree;

void InitTree(Tree *tree);
int IsEmpty_t(Tree *tree);
void insert(Tree *tree, int data);