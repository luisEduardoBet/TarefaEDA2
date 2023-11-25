#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define NUM_REPETICOES 15
#define NUM_ORDEM 10

typedef struct no {
    int* chaves;
    int numero_total;
    int* qdd;
    struct no* no_pai; 
    struct no** nos_filhos;
} No;

typedef struct arvore_B {
  No* raiz;
  int ordem;
} arvore_B;


int cont = 0;


arvore_B* criar_Arvore(int);
No* criar_No(arvore_B*);
No* localizar_No(arvore_B*, int);
int pesquisa_Binaria(No*, int);
int localizar_Chave(arvore_B*, int);
int verifica_Overflow(arvore_B*,No*);
void percorrer_Arvore(No*);
void atribui_Chave_No(No*, No*, int);
void chave_Recursiva(arvore_B*, No*, No*, int);
void adicionar_Chave(arvore_B*, int);

//Função para criar árvore
arvore_B* criar_Arvore(int ordem) {
    arvore_B* a=malloc(sizeof(arvore_B));
    a -> ordem = ordem;
    a -> raiz = criar_No(a);
    
    return a;
}



//Função para criar nó
No* criar_No(arvore_B* arvore) {
    int max=arvore->ordem*2;
    No* no=malloc(sizeof(No));
    no -> no_pai=NULL;
    no -> chaves=malloc(sizeof(int)*(max + 1));
    no -> nos_filhos=malloc(sizeof(No)*(max + 2));
    no -> qdd=malloc(sizeof(int)*(max + 2));
    no -> numero_total=0;
    for(int i = 0;i < max + 2; i++){
        no -> nos_filhos[i] = NULL;
        no -> qdd[i]=0;
    } 

    return no;
}

//Função para percorrer a árvore
void percorrer_Arvore(No* no) {

    cont++;
    if(no != NULL) {

        cont++; 
        for(int i = 0;i < no -> numero_total; i++){

            cont++;
            percorrer_Arvore(no -> nos_filhos[i]); 
            printf("%d qdd: %d\n",no -> chaves[i], no -> qdd[i]);
        }
        percorrer_Arvore(no -> nos_filhos[no->numero_total]);
    }
}

//Função para encontrar chave em um nó com pesquisa binária
int pesquisa_Binaria(No* no, int chave) {
    int inicio = 0, fim = no -> numero_total-1, metade;

    cont++;		
    while(inicio <= fim){
        cont++;

        metade = (inicio + fim)/2;

        cont++;
        if(no -> chaves[metade] == chave) 
            return metade;	
        else 
            cont++;
            if(no -> chaves[metade] > chave) 
                fim = metade-1;	
            else 
                inicio = metade + 1;
    }
    return inicio;	
}

//Esta função tenta localizar chave em cada nó
int localizar_Chave(arvore_B* arvore, int chave) {	
    No *no = arvore -> raiz;

    cont++;
    while(no != NULL){

        cont++;
        int i = pesquisa_Binaria(no, chave);

        cont++;
        if(i < no -> numero_total && no -> chaves[i] == chave) 
            return 1; 
        else 
            no = no -> nos_filhos[i];
    }
    return 0;
}

//Função que encontra o nó que deverá ser adicionada a chave
No* localizar_No(arvore_B* arvore, int chave) {	
    No *no = arvore -> raiz;

    cont++;
    while(no != NULL) {
        int i = pesquisa_Binaria(no, chave);

        cont++;
        if(no -> nos_filhos[i] == NULL) 
            return no;
        else 
            no = no -> nos_filhos[i];
    }
    return NULL;
}

//Função que adiciona chave ao nó
void atribui_Chave_No(No* no, No* novo_No, int chave){
    int i = pesquisa_Binaria(no, chave);

    cont++;
    if(no -> chaves[i] == chave){
        no -> qdd[i]++;
    }
    else{

        cont++;
        for(int j = no -> numero_total-1; j >= i; j--){

            cont++;
            no -> chaves[j+1] = no -> chaves[j];
            no -> nos_filhos[j+2] = no -> nos_filhos[j+1];
        }
        no -> chaves[i] = chave;
        no -> nos_filhos[i+1] = novo_No;
        no -> numero_total++;
    }
}

//Função que verifica se houve overflow
int verifica_Overflow(arvore_B* arvore, No* no) {
    
    cont++;
    return no -> numero_total > arvore->ordem*2;
}

//Divide chaves de um nó em um outro
No* dividir_No(arvore_B* arvore, No* no) {
    int metade = no -> numero_total/2;
    No* novo_No = criar_No(arvore);
    novo_No -> no_pai = no -> no_pai;

    cont++;
    for(int i = metade + 1;i < no -> numero_total; i++){
        cont++;

        novo_No -> nos_filhos[novo_No -> numero_total] = no -> nos_filhos[i];
        novo_No -> chaves[novo_No -> numero_total] = no -> chaves[i];

        cont++;
        if(novo_No -> nos_filhos[novo_No->numero_total] != NULL) 
            novo_No -> nos_filhos[novo_No -> numero_total] -> no_pai=novo_No;
        novo_No -> numero_total++;
    }

    novo_No -> nos_filhos[novo_No -> numero_total] = no -> nos_filhos[no -> numero_total];

    cont++;
    if(novo_No -> nos_filhos[novo_No -> numero_total] != NULL) 
        novo_No -> nos_filhos[novo_No -> numero_total] -> no_pai=novo_No;    
    no -> numero_total = metade;
    return novo_No;
}

//Função que adiciona chaves de modo recursivo
void chave_Recursiva(arvore_B* arvore, No* no, No* novo_No, int chave) {
    atribui_Chave_No(no, novo_No, chave);

    cont++;
    if(verifica_Overflow(arvore, no)){
        int escolhido = no -> chaves[arvore->ordem]; 
        No* novo_No = dividir_No(arvore, no);
        cont++;
        if(no -> no_pai == NULL){
            No* no_pai = criar_No(arvore);            
            no_pai -> nos_filhos[0] = no;
            atribui_Chave_No(no_pai, novo_No, escolhido);
            no -> no_pai = no_pai;
            novo_No -> no_pai = no_pai;
            arvore -> raiz = no_pai;
        }
        else 
            chave_Recursiva(arvore, no -> no_pai, novo_No, escolhido);
    }
}

//Função para adicionar chave
void adicionar_Chave(arvore_B* arvore, int chave) {
    No* no = localizar_No(arvore, chave);
    chave_Recursiva(arvore, no, NULL, chave);
}

//Função que compara o qsort
int compara_qsort(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

//Função para remover nós da árvore
void remover(No* no){

    if(no != NULL)
        for(int i = 0; i < no -> numero_total; i++) 
            remover(no -> nos_filhos[i]);
    free(no);
}

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
    for(int k = 1000; k <= 10000; k+=500){
    int contInserir = 0;
    int contRemover = 0;

    for(int i = 0;i < NUM_REPETICOES; i++){

        srand(time(NULL));

        arvore_B* a = criar_Arvore(NUM_ORDEM);
        cont = 0;

        int aleatorio = rand() % (k-1);
        int num_to_remove; 

        for(int j = 0; j < k; j++){
            int num = rand()%10000;
            adicionar_Chave(a, num); 

            if(aleatorio == j){ 
                num_to_remove = num;
            }

        }

        contInserir += cont;

        remover(a->raiz);

        delay(1000);

    }

    printf("Nodos: %d  | Complexidade de Inserção: %d\n", k, contInserir/NUM_REPETICOES);
    //printf("Nodos: %d  | Complexidade de Remoção: %d\n", k, contRemover/NUM_REPETICOES);

    }
}