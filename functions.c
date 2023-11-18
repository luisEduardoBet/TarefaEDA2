#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>
#include "functions.h"

void randomDataset(char* path,int n){

    FILE *p =  fopen(path, "w"); 

    if(!p)
        printf("Erro: Não foi possivel achar o path do arquivo\n");

    else{

        srand(time(NULL));

        for(int i = 0; i < n; i++){

            int random= rand() % 10000; 

            if((i+1) == n){ 
                fprintf(p, "%d", random); 
            }else{
                fprintf(p, "%d\n", random);
            }

            
        }

    }

    fclose(p);
}


void readDataset(char* path, tree *arvore){

    FILE *p = fopen(path,"r");

    if(!p) printf("Erro: Não foi possivel achar o path do arquivo\n");

    else{
        while(!feof(p)){
            int key; 
            fscanf(p, "%d",&key);
            printf("%d ", key);
            adicionar(arvore, key);
        }
    }

    fclose(p);
}

//Mostar arvore pre-ordem(esquerda, raiz,direita)

void posOrdem(node*  raiz){

    if(raiz !=  NULL){
        posOrdem(raiz->esq);
        if(raiz->pai == NULL){ 
            printf("Chave: %d | PAI: NULL \n", raiz->chave); 
        }else{
            printf("Chave: %d | PAI: %d\n ", raiz->chave, raiz->pai->chave); 
        }
         
        posOrdem(raiz->dir);
    }
}



// ---------------------------------- AVL TREE --------------------------------------------

tree* createTree(){
    
    tree *newTree = malloc(sizeof(tree));  
    newTree->root = NULL;
}

node* novoNo(int n){ 

    node* nNodo =  malloc(sizeof(node)); 
    nNodo->chave = n; 
    nNodo->pai = NULL;
    nNodo->esq = NULL;
    nNodo->dir = NULL;
    nNodo->alt = 0; 

    return nNodo; 
}

int altura(node *no){ 

    int esquerda = 0; int direita = 0; 

    if(no->esq != NULL){ 
        esquerda =  altura(no->esq) + 1; 
    }

    if (no->dir != NULL){ 
        direita = altura(no->dir)+1; 
    }

    return esquerda > direita? esquerda:direita; 

}


int fb(node * no){
    int esquerda = 0; int direita = 0; 

    if(no->esq != NULL){ 
        esquerda =  altura(no->esq) + 1; 
    }

    if (no->dir != NULL){ 
         direita = altura(no->dir)+1; 
    }

    return esquerda - direita; 
}

// Rotação Simples à esquerda
node* rse(tree* arvore, node *no){
 
    node *pai = no->pai; 
    node *direita =  no->dir; 

    no->dir = direita->esq;
    no->pai = direita; 

    direita->esq = no; 
    direita->pai = pai; 

    if(no->dir != NULL) {
        no->dir->pai = no; 
    }

    if(pai==NULL){
        arvore->root = direita  ;
    }else{
        if(pai->esq == no){
            pai->esq = direita; 
        }
        else{
            pai->dir = direita;
        }
    }   
    return direita; 
}

// Rotação Simples à Direita
node* rsd(tree* arvore, node *no){

    node *pai = no->pai; 
    node *esquerda = no->esq; 

    no->esq = esquerda->dir;
    no->pai = esquerda; 
    
    esquerda->dir= no; 
    esquerda->pai = pai;

    if(no->esq != NULL){
        no->esq->pai = no;
    } 

    if(pai==NULL){
        arvore->root = esquerda;
    }else{
        if(pai->esq == no){
            pai->esq = esquerda; 
        }
        else{
            pai->dir = esquerda;
        }
        
    }   

    return esquerda;

}

//Rotação Dupla à Esquerda

node * rde( tree* arvore, node* no){
    no->dir = rsd(arvore, no->dir); 
    return rse(arvore, no);
}

//Rotação Dupla à Direita
node *rdd(tree* arvore, node* no){
    no->esq =  rse(arvore, no->esq);
    return rsd(arvore, no); 
}



node* adicionar(tree* arvore, int n){

    if (arvore->root == NULL){
        node* no = novoNo(n);
        arvore->root = no;  
        return no; 
    }
    else{
        node* no = inserir(arvore->root, n); 
        balancear(arvore, no);
        return no;
    }
}

node* inserir(node* no, int n){

    if(n > no->chave){

        if(no->dir == NULL){
            no->dir = novoNo(n);
            no->dir->pai =  no;
        }
        else{
            return inserir(no->dir, n);
        }
    }
    else{
        if(n < no->chave){
            if(no->esq == NULL){
                no->esq = novoNo(n);
                no->esq->pai =  no;
            }
            else{
                return inserir(no->esq, n);
            }
        }
        else{
            //caso há valor repetido
            return novoNo(n);
        }
    }
    
    
}

void remover(tree* arvore, int n){

    node *no = deletar(arvore->root, n); 
    balancear(arvore, no);
}


node *deletar(node *root, int n){
    
    node* no = buscarNo(root, n); 

    if(no == NULL){ // No não foi encontrado na busca
        return NULL;
    }

    else{

        node* pai = no->pai;

        if(no->dir == NULL && no->esq == NULL){    
            if(pai->esq ==  no) pai->esq = NULL;
            else pai->dir = NULL; 
            free(no);
            return pai;
        }
        
        else{

            if(no->dir != NULL && no->esq!= NULL){
                node *aux = pegaMaior(no->esq);
                no->chave =  aux->chave; 
                no->dir->pai = no; 

                deletar(no->esq, aux->chave);

            }
            else{
                node *aux = no->esq? no->esq:no->dir;
                *no = *aux;
                no->pai = pai;
                free(aux);
            }

        }

        return no;
    }

}

void balancear(tree* arvore, node *no){

    while(no != NULL){
        int fator =  fb(no);

        if(fator > 1){
            
            if (fb(no->esq) > 0){
                rsd(arvore, no);
            }
            else{
                rdd(arvore, no);
            }

        }

        else if (fator < -1){ 

            if(fb(no->dir) < 0){
                rse(arvore, no);
            }
            else{
                rde(arvore, no);
            }
        }

        no = no->pai;
    }
}

node *buscarNo(node* root, int n){

    if (root == NULL || root->chave == n){
        return root;
    }

    if(root->chave < n) return buscarNo(root->dir, n); 
    else if (root->chave > n) return buscarNo(root->esq, n);
}

node * pegaMaior(node* no){

    if(no->dir ==NULL){
        return no; 
    }
    else return pegaMaior(no->dir);

}

