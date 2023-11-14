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

//Mostar arvore pre-ordem(raiz, esquerda, direita)

void preOrdem(node*  raiz){

    if(raiz !=  NULL){
        printf("%d ", raiz->chave); 
        preOrdem(raiz->esq); 
        preOrdem(raiz->dir);

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

// Rptação Simples à esquerda
node* rse(node *no){ 
    node *pai = no->pai; 
    node *direita =  no->dir; 

    no->dir = direita->esq; 
    no->pai = direita; 

    direita->esq = no; 
    direita-> pai = pai; 

    return direita; 
}

// Rotação Simples à Direita
node* rsd(node *no){

    node *pai = no->pai; 
    node *esquerda = no->esq; 

    no->esq = esquerda->dir;
    no->pai = esquerda; 
    
    esquerda->dir= no; 
    esquerda->pai = pai; 

}

//Rotação Dupla à Esquerda

node * rde( node* no){
    no->dir = rsd(no->dir); 
    return rse(no);
}

//Rotação Dupla à Direita
node *rdd(node* no){
    no->esq =  rse(no->esq); 
    return rsd(no);
}



node* adicionar(tree* arvore, int n){

    if (arvore->root == NULL){
        node* no = novoNo(n);
        arvore->root = no;  
        return no; 
    }
    else{
        node* no = inserir(arvore->root, n); 
        no->alt = altura(no);
        //printf("%d", no->chave);
        balancear(no);
        return no;
    }
}

node* inserir(node* no, int n){

    //Inserção comum de uma arvore de Busca Binária
    if(no == NULL){
        return (novoNo(n)); 
    }
    else{
        
        if (no->chave > n){ 
            no->esq = inserir(no->esq, n);
            no->esq->pai = no; 
            return no->esq;
        } 
        else{

            if(no->chave < n){ 
                no->dir =  inserir(no->esq,n);
                no->dir->pai = no; 
                return no->dir;
            } 
            else{ 
                return no; 
            }
        }
    }
}

void balancear(node *no){

    while(no != NULL){
        int fator =  fb(no);

        if(fator > 1){
            
            if (fb(no->esq) > 0){
                rsd(no);
            }
            else{
                rdd(no);
            }

        }

        else if (fator < -1){ 

            if(fb(no->dir) < 0){
                rse(no);
            }
            else{
                rde(no);
            }
        }

        no = no->pai;
    }
}

