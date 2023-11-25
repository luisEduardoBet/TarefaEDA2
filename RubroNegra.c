#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define REPETICOES 10
#define QTD 1000

enum coloracao {Vermelho, Preto};
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor; //cor do nó (Vermelho ou Preto)
    int valor;
    int qtd; 
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} Arvore;

int cont=0;

No* criarNo(Arvore*, No*, int);
Arvore* criar();
int vazia(Arvore*); //parada
No* adicionar(Arvore*, int);
void rotacionarEsquerda(Arvore* arvore, No* no);
void rotacionarDireita(Arvore* arvore, No* no);
void balancear(Arvore* arvore, No* no);

//Cria a árvore
Arvore* criar() {
    Arvore *arvore=malloc(sizeof(Arvore));
    arvore->nulo=NULL;
    arvore->raiz=NULL;
    arvore->nulo=criarNo(arvore, NULL, 0);
    arvore->nulo->cor=Preto;
    return arvore;
}

//Verifica se a árvore está vazia
int vazia(Arvore* arvore) {
    return arvore->raiz==NULL;
}

//Criação de nó: com cor vermelha
No* criarNo(Arvore* arvore, No* pai, int valor) {
    No* no=malloc(sizeof(No));
    no->pai=pai;    
    no->valor=valor;
    no->direita=arvore->nulo;
    no->esquerda=arvore->nulo;
    no->qtd=1;
    return no;
}

//Remove todos os nodos de uma árvore
void remover(Arvore* arvore, No* no) {
    if(no->esquerda!=arvore->nulo) 
        remover(arvore, no->esquerda); 
    if(no->direita!=arvore->nulo)  
        remover(arvore, no->direita);
    if(no->pai==arvore->nulo) 
        arvore->raiz=arvore->nulo;
    else{
        if(no->pai->esquerda==no) 
            no->pai->esquerda=arvore->nulo;
        else 
            no->pai->direita=arvore->nulo;
    }
    free(no);
}

//Adiciona nodo na árvore 2: procura lugar a inserir ou aumenta a quantidade caso já exista
No* adicionarNo(Arvore* arvore, No* no, int valor) {
    cont++;
    if(valor>no->valor){
        if(no->direita==arvore->nulo){
            no->direita=criarNo(arvore, no, valor);     
            no->direita->cor=Vermelho;
            no->qtd=1;        
            return no->direita;
        }else 
            return adicionarNo(arvore, no->direita, valor); 

    }else if(valor<no->valor){
        if(no->esquerda==arvore->nulo){
            no->esquerda=criarNo(arvore, no, valor);
            no->esquerda->cor=Vermelho;
            no->qtd=1; 
            return no->esquerda;
        }else 
            return adicionarNo(arvore, no->esquerda, valor);
    }else{
          no->qtd++;
          return no;
    } 
}

No* adicionar(Arvore* arvore, int valor) {
    cont++;
    if(vazia(arvore)){
        arvore->raiz=criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor=Preto;
        return arvore->raiz;
    }else{
        No* no=adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);   
        return no;
    }
}

void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if(no!=arvore->nulo){
        percorrerProfundidadeInOrder(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePreOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if(no!=arvore->nulo){
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(Arvore* arvore, No* no, void (callback)(int)) {
    if(no!=arvore->nulo){
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balancear(Arvore* arvore, No* no) {
    while(no->pai->cor==Vermelho){ //Garante que todos os niveis foram balanciados
        cont++;
        if(no->pai==no->pai->pai->esquerda){
            No *tio=no->pai->pai->direita; // tio é o nodo da direita e pai o da esquerda
            if(tio->cor==Vermelho){ //Caso 2
                tio->cor=Preto;               
                no->pai->cor=Preto;           
                no->pai->pai->cor = Vermelho; 
                no=no->pai->pai; //Vai pro nível anterior
            }else{
                if(no==no->pai->direita){ //Caso 3
                    no=no->pai; //Rotaciona a esquerda no pai
                    rotacionarEsquerda(arvore, no); 
                }else{ //Caso 4  
                    no->pai->cor=Preto;         
                    no->pai->pai->cor=Vermelho; 
                    rotacionarDireita(arvore, no->pai->pai); //Rotação à direita no avô
                }
            }
        }else{
            No *tio=no->pai->pai->esquerda; //tio é o nodo da esquerda e pai o da direita
            if(tio->cor==Vermelho){ //Caso 2
                tio->cor=Preto;             
                no->pai->cor=Preto;         
                no->pai->pai->cor=Vermelho; 
                no=no->pai->pai; //Vai pro nível anterior
            }else{
                if(no==no->pai->esquerda){  //Caso 3
                    no=no->pai; //Rotaciona a direita no pai
                    rotacionarDireita(arvore, no);
                }else{ //Caso 4
                    no->pai->cor=Preto;        
                    no->pai->pai->cor=Vermelho;
                    rotacionarEsquerda(arvore, no->pai->pai); //Rotação à esquerda no avô
                }
            }
        }
    }
    arvore->raiz->cor=Preto; //Caso 1
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    cont++;

    No* direita=no->direita;
    no->direita=direita->esquerda; 

    if(direita->esquerda!=arvore->nulo) 
        direita->esquerda->pai=no; //Se houver filho à esquerda em direita, ele será pai do nó

    direita->pai=no->pai; //Ajusta no pai do nó à direita

    if(no->pai==arvore->nulo) 
        arvore->raiz=direita; //Se nó for raiz, o nó direita será a nova raiz da árvore
    else if(no==no->pai->esquerda) 
        no->pai->esquerda=direita; //Corrige relação pai-filho do novo pai (esquerda)
    else 
        no->pai->direita=direita; //Corrige relação pai-filho do novo pai (direita)

    direita->esquerda=no; //Corrige relação pai-filho entre o nó pivô e o nó à direita
    no->pai=direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    cont++;

    No* esquerda=no->esquerda;
    no->esquerda=esquerda->direita;

    if(esquerda->direita!=arvore->nulo) 
        esquerda->direita->pai=no; //Se houver filho à direita em esquerda, ele será pai do nó


    esquerda->pai=no->pai; //Ajusta no pai do nó à esquerda

    if(no->pai==arvore->nulo) 
        arvore->raiz=esquerda; //Se nó for raiz, o nó esquerda será a nova raiz da árvore
    else if(no==no->pai->esquerda) 
        no->pai->esquerda=esquerda;  //Corrige relação pai-filho do novo pai (esquerda)
    else 
        no->pai->direita=esquerda; //Corrige relação pai-filho do novo pai (direita)
    
    esquerda->direita=no; //Corrige relação pai-filho entre o nó pivô e o nó à esquerda
    no->pai=esquerda;
}

//comparador do qsort
int comparador(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

// Função para encontrar o nó mínimo a partir de um determinado nó
No* encontrarMinimo(Arvore* arvore, No* no) {
    while (no->esquerda != arvore->nulo && no->esquerda->qtd != 0) {
        no = no->esquerda;
    }
    return no;
}

// Função para encontrar o sucessor de um nó
No* encontrarSucessor(Arvore* arvore, No* no) {
    if (no->direita != arvore->nulo && no->direita->qtd != 0) {
        return encontrarMinimo(arvore, no->direita);
    }

    No* pai = no->pai;
    while (pai != arvore->nulo && no == pai->direita) {
        no = pai;
        pai = pai->pai;
    }

    return pai;
}

// Função auxiliar para substituir um nó pelo seu filho à direita na árvore
void transplant(Arvore* arvore, No* u, No* v) {
    if(u == arvore->nulo){
        return;
    }
    if (u->pai == arvore->nulo) {
        arvore->raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }

    if (v != arvore->nulo) {
        v->pai = u->pai;
    }
}

// Função para encontrar um nó com um determinado valor na árvore
No* encontrarNo(Arvore* arvore, No* no, int valor) {
    if (no == arvore->nulo || no->qtd == 0) {
        return NULL;
    }

    if (valor < no->valor) {
        return encontrarNo(arvore, no->esquerda, valor);
    } else if (valor > no->valor) {
        return encontrarNo(arvore, no->direita, valor);
    } else {
        return no;
    }
}

void deleteFixup(Arvore* arvore, No* x) {
    while (x != arvore->raiz && (x == arvore->nulo || x->cor == Preto)) {
        if (x == x->pai->esquerda) {
            No* w = x->pai->direita;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, x->pai);
                w = x->pai->direita;
            }
            if ((w->esquerda == arvore->nulo || w->esquerda->cor == Preto) &&
                (w->direita == arvore->nulo || w->direita->cor == Preto)) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->direita == arvore->nulo || w->direita->cor == Preto) {
                    if (w->esquerda != arvore->nulo) {
                        w->esquerda->cor = Preto;
                    }
                    w->cor = Vermelho;
                    rotacionarDireita(arvore, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                if (w->direita != arvore->nulo) {
                    w->direita->cor = Preto;
                }
                rotacionarEsquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        } else {
            No* w = x->pai->esquerda;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarDireita(arvore, x->pai);
                w = x->pai->esquerda;
            }
            if ((w->direita == arvore->nulo || w->direita->cor == Preto) &&
                (w->esquerda == arvore->nulo || w->esquerda->cor == Preto)) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->esquerda == arvore->nulo || w->esquerda->cor == Preto) {
                    if (w->direita != arvore->nulo) {
                        w->direita->cor = Preto;
                    }
                    w->cor = Vermelho;
                    rotacionarEsquerda(arvore, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                if (w->esquerda != arvore->nulo) {
                    w->esquerda->cor = Preto;
                }
                rotacionarDireita(arvore, x->pai);
                x = arvore->raiz;
            }
        }
    }
    if (x != arvore->nulo) {
        x->cor = Preto;
    }
}


// Função para excluir um nó da árvore rubro-negra com base em seu valor
int deleteNo(Arvore* arvore, int valor) {
    int i;
    No* no = encontrarNo(arvore, arvore->raiz, valor);

    i++;
    if (no == arvore->nulo) {
        printf("Nó com valor %d não encontrado na árvore.\n", valor);
        return 0;
    }

    No* y = no;
    No* x;
    Cor corOriginal = y->cor;

    i++;
    if (no->esquerda == arvore->nulo || no->esquerda->qtd == 0) {
        x = no->direita;
        transplant(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo || no->direita->qtd == 0) {
        i++;
        x = no->esquerda;
        transplant(arvore, no, no->esquerda);
    } else {
        i++;
        y = encontrarSucessor(arvore, no);
        corOriginal = y->cor;
        x = y->direita;

        i++;
        if (y->pai == no) {
            x->pai = y;
        } else {
            transplant(arvore, y, y->direita);
            y->direita = no->direita;
            y->direita->pai = y;
        }

        transplant(arvore, no, y);
        y->esquerda = no->esquerda;
        y->esquerda->pai = y;
        y->cor = no->cor;
    }

    free(no);

    i++;
    if (corOriginal == Preto) {
        deleteFixup(arvore, x);
    }

    return i;
}


int main() {
    int contadores[QTD];
    int num;
    for(int i=0;i<QTD;i++) 
        contadores[i]=0;

    srand(time(NULL));

    int contadorCasoMedio=0;
    for(int i=0;i<REPETICOES;i++){
        Arvore* a = criar();
        cont=0;
        for(int j=0;j<QTD;j++){
            num=rand()%1000;
            adicionar(a,num);
            contadores[j]+=cont;
        }
        remover(a, a->raiz);
        contadorCasoMedio+=cont;
    }

    Arvore* a = criar();
        cont=0;
        for(int j=0;j<QTD;j++){
            int n=rand()%1000;
            if(j==5){
                num = n;
            }
            adicionar(a,num);
        }

    int d = deleteNo(a,num);

    printf("deleta = %i\n",d);

    for(int i=49;i<QTD;i+=50) 
        printf("%d\n", i+1);
    
    printf("\n\n\n");

    for(int i=49;i<QTD;i+=50) 
        printf("%d\n", contadores[i]/REPETICOES);
    
    printf("Media para o caso medio: %d\n\n", contadorCasoMedio/REPETICOES);
}