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

arvore_B* criar_Arvore(int);
No* criar_No(arvore_B*);
No* localizar_No(arvore_B*, int);
int pesquisa_Binaria(No*, int);
int localizar_Chave(arvore_B*, int);
int verifica_Overflow(arvore_B*,No*);
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

int contador = 0;

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

//Função para encontrar chave em um nó com pesquisa binária
int pesquisa_Binaria(No* no, int chave) {

    int inicio = 0, fim = no -> numero_total-1, metade;	
    contador++;	
    while(inicio <= fim){	
        metade = (inicio + fim)/2;
        contador++;
        if(no -> chaves[metade] == chave) 
            return metade;	
        else 
            contador++;
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

    contador++;
    while(no != NULL){

        contador++;
        int i = pesquisa_Binaria(no, chave);
        contador++;
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

    contador++;
    while(no != NULL) {
        contador++;
        int i = pesquisa_Binaria(no, chave);

        contador++;
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
    contador++;
    if(no -> chaves[i] == chave){
        no -> qdd[i]++;
    }
    else{

        contador++;
        for(int j = no -> numero_total-1; j >= i; j--){
            contador++;
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
    contador++;
    return no -> numero_total > arvore->ordem*2;
}

//Divide chaves de um nó em um outro
No* dividir_No(arvore_B* arvore, No* no) {
    int metade = no -> numero_total/2;
    No* novo_No = criar_No(arvore);
    novo_No -> no_pai = no -> no_pai;
    
    contador++;
    for(int i = metade + 1;i < no -> numero_total; i++){
        contador++;

        novo_No -> nos_filhos[novo_No -> numero_total] = no -> nos_filhos[i];
        novo_No -> chaves[novo_No -> numero_total] = no -> chaves[i];
        
        contador++;
        if(novo_No -> nos_filhos[novo_No->numero_total] != NULL) 
            novo_No -> nos_filhos[novo_No -> numero_total] -> no_pai=novo_No;
        novo_No -> numero_total++;
    }

    novo_No -> nos_filhos[novo_No -> numero_total] = no -> nos_filhos[no -> numero_total];

    contador++;
    if(novo_No -> nos_filhos[novo_No -> numero_total] != NULL) 
        novo_No -> nos_filhos[novo_No -> numero_total] -> no_pai=novo_No;    
    no -> numero_total = metade;
    return novo_No;
}

//Função que adiciona chaves de modo recursivo
void chave_Recursiva(arvore_B* arvore, No* no, No* novo_No, int chave) {
    atribui_Chave_No(no, novo_No, chave);

    contador++;
    if(verifica_Overflow(arvore, no)){
        int escolhido = no -> chaves[arvore->ordem]; 
        No* novo_No = dividir_No(arvore, no);
        
        contador++;
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


//Função para remover nós da árvore
void remover(No* no){
    if(no != NULL)
        for(int i = 0; i < no -> numero_total; i++) 
            remover(no -> nos_filhos[i]);
    free(no);
}

// Função para encontrar o nó que contém a chave a ser removida
No* encontrar_No_Remocao(arvore_B* arvore, int chave) {
    No *no = arvore -> raiz;
    contador++;
    while (no != NULL) {
        contador++;
        int i = pesquisa_Binaria(no, chave);
        contador++;
        if (i < no -> numero_total && no -> chaves[i] == chave)
            return no;
        else
            no = no -> nos_filhos[i];
    }
    return NULL;
}

// Função auxiliar para remover uma chave de um nó
void remover_Chave_No(No* no, int indice) {
    contador++;
    for (int i = indice; i < no -> numero_total - 1; i++) {
        contador++;
        no -> chaves[i] = no -> chaves[i + 1];
        no -> nos_filhos[i + 1] = no -> nos_filhos[i + 2];
    }
    no->numero_total--;
}

// Função auxiliar para encontrar o predecessor de uma chave
int encontrar_Predecessor(No* no) {
    contador++;
    while (no -> nos_filhos[no -> numero_total] != NULL){
        contador++;
        no = no -> nos_filhos[no -> numero_total];
    }   
    return no -> chaves[no -> numero_total - 1];
}

// Função para remover uma chave de um nó
void remover_Chave(arvore_B* arvore, No* no, int chave) {
    int indice = pesquisa_Binaria(no, chave);
    contador++;
    if (indice < no -> numero_total && no -> chaves[indice] == chave) {
        // Caso 1: Chave está no nó folha
        contador++;
        if (no->nos_filhos[indice] == NULL) {
            remover_Chave_No(no, indice);
        } else {
            // Caso 2: Chave está em um nó interno
            int predecessor = encontrar_Predecessor(no->nos_filhos[indice]);
            no->chaves[indice] = predecessor;
            remover_Chave(arvore, no->nos_filhos[indice], predecessor);
        }
    } else {
        // Caso 3: Chave não está no nó atual, deve ser em um dos filhos
        contador++;
        if (no->nos_filhos[indice] == NULL) {
            return;
        }
        remover_Chave(arvore, no->nos_filhos[indice], chave);
    }
}

// Função principal para remover uma chave da árvore B
void remover_Chave_Arvore(arvore_B* arvore, int chave) {
    No* no = encontrar_No_Remocao(arvore, chave);
    
    contador++;
    if (no != NULL) {
        remover_Chave(arvore, no, chave);
        contador++;
        if (no -> numero_total == 0 && no == arvore -> raiz) {
            free(no);
            arvore->raiz = NULL;
        }
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


//Loop para gerar o número de nós de forma mais "automatizada"
for(int k = 1000; k <= 10000; k+=500){
    int contInserir = 0;
    int contRemover = 0;

    for(int i = 0;i < NUM_REPETICOES; i++){

        srand(time(NULL));
        arvore_B* a = criar_Arvore(NUM_ORDEM);

        contador = 0;

        int aleatorio = rand() % (k-1);

        int num_to_remove;
        
        for(int j = 0; j < k; j++){
            int num = rand()%10000;
            adicionar_Chave(a,num);
            
            //Pega um numero aleatorio que foi inserido na arvore
            if(aleatorio == j){ 
                num_to_remove = num;
            }
        }

        contInserir += contador;

        contador = 0; 
        remover_Chave_Arvore(a, num_to_remove);
        contRemover += contador; 
         
        remover(a->raiz);

        //Gera um delay de 1 segundo para atualizar a seed do srand( )
        delay(1000);

    }
    //Printa a Média dos Esforços encontrados.
    printf("Nodos: %d  | Complexidade de Inserção: %d\n", k, contInserir/NUM_REPETICOES);
    printf("Nodos: %d  | Complexidade de Remoção: %d\n", k, contRemover/NUM_REPETICOES);

    }
}