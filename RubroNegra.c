#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define REPETICOES 15
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

    cont++;
    if(no->esquerda!=arvore->nulo){
        remover(arvore, no->esquerda);
    } 
    cont++;
    if(no->direita!=arvore->nulo){
        remover(arvore, no->direita);
    }
    cont++;
    if(no->pai==arvore->nulo){ 
        arvore->raiz=arvore->nulo;
    }else{
        cont++;
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
        cont++;
        if(no->direita==arvore->nulo){
            no->direita=criarNo(arvore, no, valor);     
            no->direita->cor=Vermelho;
            no->qtd=1;        
            return no->direita;
        }else 
            return adicionarNo(arvore, no->direita, valor); 

    }else{
        cont++;
        if(valor<no->valor){
            cont++;
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

void balancear(Arvore* arvore, No* no) {
    cont++;
    while(no->pai->cor==Vermelho){ //Garante que todos os niveis foram balanciados
        cont++;
        cont++;
        if(no->pai==no->pai->pai->esquerda){
            No *tio=no->pai->pai->direita; // tio é o nodo da direita e pai o da esquerda
            cont++;
            if(tio->cor==Vermelho){ //Caso 2
                tio->cor=Preto;               
                no->pai->cor=Preto;           
                no->pai->pai->cor = Vermelho; 
                no=no->pai->pai; //Vai pro nível anterior
            }else{
                cont++;
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
            cont++;
            if(tio->cor==Vermelho){ //Caso 2
                tio->cor=Preto;             
                no->pai->cor=Preto;         
                no->pai->pai->cor=Vermelho; 
                no=no->pai->pai; //Vai pro nível anterior
            }else{
                cont++;
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

    No* direita=no->direita;
    no->direita=direita->esquerda; 

    cont++;
    if(direita->esquerda!=arvore->nulo) 
        direita->esquerda->pai=no; //Se houver filho à esquerda em direita, ele será pai do nó

    direita->pai=no->pai; //Ajusta no pai do nó à direita

    cont++;
    if(no->pai==arvore->nulo) 
        arvore->raiz=direita; //Se nó for raiz, o nó direita será a nova raiz da árvore
    else {
        cont++;
        if(no==no->pai->esquerda) 
            no->pai->esquerda=direita; //Corrige relação pai-filho do novo pai (esquerda)
        else 
            no->pai->direita=direita; //Corrige relação pai-filho do novo pai (direita)
    }
    direita->esquerda=no; //Corrige relação pai-filho entre o nó pivô e o nó à direita
    no->pai=direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {

    No* esquerda=no->esquerda;
    no->esquerda=esquerda->direita;

    cont++;
    if(esquerda->direita!=arvore->nulo) 
        esquerda->direita->pai=no; //Se houver filho à direita em esquerda, ele será pai do nó


    esquerda->pai=no->pai; //Ajusta no pai do nó à esquerda

    cont++;
    if(no->pai==arvore->nulo) 
        arvore->raiz=esquerda; //Se nó for raiz, o nó esquerda será a nova raiz da árvore
    else{
        cont++;
        if(no==no->pai->esquerda) 
            no->pai->esquerda=esquerda;  //Corrige relação pai-filho do novo pai (esquerda)
        else 
            no->pai->direita=esquerda; //Corrige relação pai-filho do novo pai (direita)
    }
    esquerda->direita=no; //Corrige relação pai-filho entre o nó pivô e o nó à esquerda
    no->pai=esquerda;
}

// Função para encontrar o nó mínimo a partir de um determinado nó
No* encontrarMinimo(Arvore* arvore, No* no) {
    cont++;
    while (no->esquerda != arvore->nulo && no->esquerda->qtd != 0) {
        cont++;
        no = no->esquerda;
    }
    return no;
}

// Função para encontrar o sucessor de um nó
No* encontrarSucessor(Arvore* arvore, No* no) {
    cont++;
    if (no->direita != arvore->nulo && no->direita->qtd != 0) {
        return encontrarMinimo(arvore, no->direita);
    }

    No* pai = no->pai;
    cont++;
    while (pai != arvore->nulo && no == pai->direita) {
        cont++;
        no = pai;
        pai = pai->pai;
    }

    return pai;
}

// Função auxiliar para substituir um nó pelo seu filho à direita na árvore
void transplant(Arvore* arvore, No* u, No* v) {
    cont++;
    if(u == arvore->nulo){
        return;
    }
    cont++;
    if (u->pai == arvore->nulo) {
        arvore->raiz = v;
    } else{
        cont++;
        if (u == u->pai->esquerda) {
            u->pai->esquerda = v;
        } 
        else {
            u->pai->direita = v;
        }
    }
    cont++;
    if (v != arvore->nulo) {
        v->pai = u->pai;
    }
}

// Função para encontrar um nó com um determinado valor na árvore
No* encontrarNo(Arvore* arvore, No* no, int valor) {
    cont++;
    if (no == arvore->nulo || no->qtd == 0) {
        return NULL;
    }
    cont++;
    if (valor < no->valor) {
        return encontrarNo(arvore, no->esquerda, valor);
    } else{
        cont++;
        if (valor > no->valor) {
            return encontrarNo(arvore, no->direita, valor);
        } 
        else {
            return no;
        }
    }
}

void deleteFixup(Arvore* arvore, No* x)
{
    No* pai = arvore->nulo;
    No* avo = arvore->nulo;

    cont++;
    while ((x != arvore->raiz) && (x->cor != Preto) && (x->pai->cor == Vermelho))
    {
        cont++;
        pai = x->pai;
        avo = x->pai->pai;

        cont++;
        if (pai == avo->esquerda)
        {
            No* tio = avo->direita;
            cont++;
            if (tio != arvore->nulo && tio->cor == Vermelho)
            {
                avo->cor = Vermelho;
                pai->cor = Preto;
                tio->cor = Preto;
                x = avo;
            }
            else {
                cont++;
                if (x == avo->direita) {
                    rotacionarEsquerda(arvore, pai);
                    x = pai;
                    pai = x->pai;
                }

                rotacionarDireita(arvore, avo);
                int t = pai->cor;
                pai->cor = avo->cor;
                avo->cor = t;
                x = pai;
            }
        }
        else {
            No* tio = avo->esquerda;
            cont++;
            if ((tio != arvore->nulo) && (tio->cor == Vermelho))
            {
                avo->cor = Vermelho;
                pai->cor = Preto;
                tio->cor = Preto;
                x = avo;
            }
            else {
                cont++;
                if (x == pai->esquerda) {
                    rotacionarDireita(arvore, pai);
                    x = pai;
                    pai = x->pai;
                }
                rotacionarEsquerda(arvore, avo);
                int t = pai->cor;
                pai->cor = avo->cor;
                avo->cor = t;
                x = pai;
            }
        }
    }

    arvore->raiz->cor = Preto;
}



// Função para excluir um nó da árvore rubro-negra com base em seu valor
void deleteNo(Arvore* arvore, int valor) {
    No* no = encontrarNo(arvore, arvore->raiz, valor);

    cont++;
    if (no == arvore->nulo) {
        printf("Nó com valor %d não encontrado na árvore.\n", valor);
        return;
    }

    No* y = no;
    No* x;
    Cor corOriginal = y->cor;

    cont++;
    if (no->esquerda == arvore->nulo || no->esquerda->qtd == 0) {
        x = no->direita;
        transplant(arvore, no, no->direita);
    } else{
        cont++;
        if (no->direita == arvore->nulo || no->direita->qtd == 0) {
        x = no->esquerda;
        transplant(arvore, no, no->esquerda);
        } 
        else {
            y = encontrarSucessor(arvore, no);
            corOriginal = y->cor;
            x = y->direita;

            cont++;
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
    }

    free(no);

    cont++;
    if (corOriginal == Preto) {
        deleteFixup(arvore, x);
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



int main() {


for(int k = 1000;  k <= 10000; k+=500){
    int num;
    int n; 
    int contadorInserir = 0; 
    int contadorRemover = 0;
    srand(time(NULL));

    for(int i=0;i<REPETICOES;i++){
        Arvore* a = criar();

        cont=0;

        int c = rand() % (k-1);

        for(int j=0;j < k;j++){
            num=rand()%10000;
            adicionar(a,num);

            if(j==(c)){

                n = num;
            }
        }
        contadorInserir+=cont;
        cont = 0;

        deleteNo(a,n);
        contadorRemover+= cont;
        
        remover(a, a->raiz);

        delay(1000);
    }
    
    printf("Nodos: %d  | Esforço de Inserção: %d\n", k, contadorInserir/REPETICOES);
    printf("Nodos: %d  | Esforço de Remoção: %d\n", k, contadorRemover/REPETICOES);
}
}