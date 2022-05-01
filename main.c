#include <stdio.h>
#include "rdp.h"
#include <stdlib.h>
#include <string.h>
#include "leerMatriz.h"

int main(){

rdp_o myrdp;

new_rdp(&myrdp);

myrdp.metodos->printNumero(&myrdp);

int matriz[2][2];
leer_matriz(2,2,matriz[0],"archivo");

for(int i = 0;i<2;i++){
    for(int j = 0; j<2;j++){
        printf("%d ",matriz[i][j]);
    }
    printf("\n");
}
}

