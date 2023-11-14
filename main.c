#include <stdio.h> 
#include "functions.h"

#define PATH "dataset.txt"

int main(){

    //Randomiza um arquivo txt com n números pseudo-aleatórios. O valor de n é passado na função
    randomDataset(PATH,3);

    tree *arvore =  createTree(); 

    readDataset(PATH, arvore);

    printf("\n\n"); 

    preOrdem(arvore->root);    

}




