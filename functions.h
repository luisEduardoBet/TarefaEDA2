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
void posOrdem(node*  raiz);
tree* createTree();
node* novoNo(int n);
int altura(node *no);
int fb(node * no);
node* rse(tree* arvore,node *no);
node* rsd(tree* arvore,node *no);
node * rde(tree* arvore, node* no);
node *rdd(tree* arvore,node* no);
node* adicionar(tree* arvore, int n);
node* inserir(node* no, int n);
void remover(tree* arvore, int n);
node* deletar(node * root, int n);
node *buscarNo(node* root, int n);
node * pegaMaior(node* no);
void balancear(tree* arvore, node *no); 

#endif