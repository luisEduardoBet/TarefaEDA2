#include <stdio.h> 
#include "functions.h"

#define PATH "dataset.txt"

int main(){

    //Randomiza um arquivo txt com n números ps eudo-aleatórios. O valor de n é passado na função
    randomDataset(PATH,14);    

    tree *arvore =  createTree(); 

    readDataset(PATH, arvore);

    printf("\n\n"); 

    posOrdem(arvore->root);
    //Um pequeno menu para facilar a remocao do nos

    //int x = 1;
    // while(x){

    //     printf("\n[0] - Sair do Programa:\n"); 
    //     printf("[1] - Deletar um número:\n");
    //     scanf("%d", &x);
        
    //     if(x){
    //         int num;
    //         printf("Digite o número que deseja deletar:\n"); 
    //         scanf("%d", &num); 
            
    //         remover(arvore, num);
    //         posOrdem(arvore->root);
    //         printf("\n");

    //     }

    // }
        

}




