#include <stdio.h> 
#include "functions.h"

#define PATH "dataset.txt"

int main(){

    //Randomiza um arquivo txt com n números ps eudo-aleatórios. O valor de n é passado na função
    randomDataset(PATH,10);    

    tree *arvore =  createTree(); 

    readDataset(PATH, arvore);

    printf("\n\n"); 

    printf("%d\n", altura(arvore->root)+1);

    posOrdem(arvore->root);    

}




