#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>


#define NUM_REPETICOES 15

//contador
int cont = 0; 

typedef struct Node{

    int chave; 
    struct Node *pai; 
    struct Node *esq; 
    struct Node *dir; 
    int altura; 

} node; 


typedef struct Tree{
    node *root; 
} tree;

int maior(int, int);
void inOrdem(node*  raiz);
void removerTodos(node*  raiz);
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
void delay(int milliseconds);

int main(){


//Loop para gerar o número de nós de forma mais "automatizada"
for(int k = 1000; k <= 10000; k+=500){
    int contInserir = 0;
    int contRemover = 0;

    for(int i = 0;i < NUM_REPETICOES; i++){

        srand(time(NULL));
        tree* a = createTree();
        cont = 0;

        int aleatorio = rand() % (k-1);

        int num_to_remove; 
        for(int j = 0; j < k; j++){
            int num = rand()%10000;
            adicionar(a,num);


            //Pega um numero aleatorio que foi inserido na arvore
            if(aleatorio == j){ 
                num_to_remove = num;
            }
        }

        contInserir += cont;

        cont = 0; 

        remover(a, num_to_remove);
        contRemover += cont;  

        removerTodos(a->root);


        //Gera um delay de 1 segundo para atualizar a seed do srand( )
        delay(1000);
    }

    //Printa a Média do esforço!!
    printf("Nodos: %d  | Esforço de Inserção: %d\n", k, contInserir/NUM_REPETICOES);
    printf("Nodos: %d  | Esforço de Remoção: %d\n", k, contRemover/NUM_REPETICOES);

    }
}


//Função que gera um delay. Utilizada para atualizar a seed do srand()
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}


// Printa a arvore inOrdem(Lado Esquerdo, Raiz, Lado direito)
void inOrdem(node*  raiz){

    if(raiz !=  NULL){
        inOrdem(raiz->esq);
        if(raiz->pai == NULL){ 
            printf("Chave: %d | PAI: NULL | Altura: %d\n", raiz->chave, raiz->altura); 
        }else{
            printf("Chave: %d | PAI: %d |Altura: %d \n", raiz->chave, raiz->pai->chave, raiz->altura); 
        }
         
        inOrdem(raiz->dir);
    }
}

//Percorre a arvore em Pos-Ordem (Transversal) e remove todos os nós da arvore
void removerTodos(node*  raiz){

    if(raiz == NULL){
        return;
    }

    removerTodos(raiz->esq);
    removerTodos(raiz->dir);

    free(raiz);

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
    nNodo->altura = 1; 

    return nNodo; 
}


int altura(node *no){ 

   cont++;  
   if(no == NULL) return 0; 

   return no->altura; 

}

// Calcula o fator de balanceamento em um nó
int fb(node * no){
  cont++;
  if (no == NULL) return 0;
  return altura(no->esq) - altura(no->dir); 
}

// Rotação Simples à esquerda
node* rse(tree* arvore, node *no){
    
    node *pai = no->pai; 
    node *direita =  no->dir; 

    no->dir = direita->esq;
    no->pai = direita; 

    direita->esq = no; 
    direita->pai = pai; 

    cont++;
    if(no->dir != NULL) {
        no->dir->pai = no; 
    }

    no->altura = maior(altura(no->esq),altura(no->dir))+1;
    direita->altura = maior(altura(direita->esq),altura(direita->dir))+1;

    cont++; 
    if(pai==NULL){
        arvore->root = direita  ;
    }else{
        cont++;
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

    cont++;
    if(no->esq != NULL){
        no->esq->pai = no;
    } 
    no->altura = maior(altura(no->esq),altura(no->dir))+1;
    esquerda->altura = maior(altura(esquerda->esq),altura(esquerda->dir))+1;
    
    cont++;
    if(pai==NULL){
        arvore->root = esquerda;
    }else{
        cont++;
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

//Retorna o maior entre dois numeros
int maior(int a, int b){
    cont++;
    return a > b ? a: b; 
}

// Função principal para a adição de um novo nó na arvore
node* adicionar(tree* arvore, int n){

    cont++;
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

//Insere o novo nó na estrutura 
node* inserir(node* no, int n){
    cont++;
    if(n > no->chave){
        cont++;
        if(no->dir == NULL){
            no->dir = novoNo(n);
            no->dir->pai =  no;
        }
        else{
            return inserir(no->dir, n);
        }
    }
    else{
        cont++;
        if(n < no->chave){
            cont++;
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
            return no;
        }
    }
    
    
}

//Função principal para remover um nó da arvore
void remover(tree* arvore, int n){
    node *no = deletar(arvore->root, n);
    balancear(arvore, no);
}


node *deletar(node *root, int n){
    
    node* no = buscarNo(root, n); 
    cont++;
    if(no == NULL){ // No não foi encontrado na busca
        return NULL;
    }

    else{

        node* pai = no->pai;
        cont++;
        if(no->dir == NULL && no->esq == NULL){     //Caso 1: O nó que vai ser removido é um nó folha
            cont++;
            if(pai->esq ==  no) pai->esq = NULL;
            else pai->dir = NULL; 
            free(no);
            return pai;
        }
        
        else{
            cont++;
            if(no->dir != NULL && no->esq!= NULL){ //Caso 2: O nó que vai ser removido é pai de 2 filhos
                node *aux = pegaMaior(no->esq);
                no->chave =  aux->chave; 
                no->dir->pai = no; 

                deletar(no->esq, aux->chave);

            }
            else{               //Caso 3: O nó que vai ser removido é pai de 1 filho
                cont++;
                node *aux = no->esq? no->esq:no->dir;
                *no = *aux;
                no->pai = pai;
                free(aux);
            }

        }

        return no;
    }

}

//Reliza o balaceamento da arvore
void balancear(tree* arvore, node *no){
    cont++;
    while(no != NULL){
        cont++;
        no->altura = 1 + maior(altura(no->esq), altura(no->dir));
        int fator =  fb(no);

        cont++;
        if(fator > 1){
            cont++;
            if (fb(no->esq) > 0){
                rsd(arvore, no);
            }
            else{
                rdd(arvore, no);
            }

        }
        else{ 
            cont++;
            if (fator < -1){ 
                cont++;
                if(fb(no->dir) < 0){
                    rse(arvore, no);
                }
                else{
                    rde(arvore, no);
                }
            }
        }

        no = no->pai;
    }
}

node *buscarNo(node* root, int n){
    cont++;
    if (root == NULL || root->chave == n){
        return root;
    }

    cont++;
    if(root->chave < n) return buscarNo(root->dir, n); 
    else{
        cont++;
        if (root->chave > n) return buscarNo(root->esq, n);
    }
}

/// Funçao para pegar o maior número localiza na sub-árvore à esquerda de um nó.
// Utilizada no Caso 2 da remoção
node * pegaMaior(node* no){
    cont++;
    if(no->dir ==NULL){
        return no; 
    }
    else return pegaMaior(no->dir);

}



