#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Node{

    int chave; 
    struct Node *pai; 
    struct Node *esq; 
    struct Node *dir; 
    int alt; 

} node; 


typedef struct Tree{
    node *root; 
} tree;

void randomDataset(char* path,int n);
void readDataset(char* path, tree *arvore); 
void preOrdem(node*  raiz);
tree* createTree();
node* novoNo(int n);
int altura(node *no);
int fb(node * no);
node* rse(node *no);
node* rsd(node *no);
node * rde( node* no);
node *rdd(node* no);
node* adicionar(tree* arvore, int n);
node* inserir(node* no, int n);
void balancear(node *no); 

#endif