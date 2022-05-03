#include "politica.h"
#include <stdio.h>

void printNumero(politica_o * rdp){
    printf("Numero: %d \n",rdp->numero);
}

int signalPolitic (politica_o *politica, int *boolQuesWait){
    // int *aux = pn.getSensitized();
    int *aux;
    if(boolQuesWait[politica->addBuffer[0]] &&  boolQuesWait[politica->addBuffer[1]] && aux[politica->addBuffer[0]] ==1 ){
        // politica->markVector = pn.getMarkVector();
        if(politica->markVector[politica->listBuff[0]] < politica->markVector[politica->listBuff[1]]){
            return politica->addBuffer[0];
        }
        else if (politica->markVector[politica->listBuff[0]] >= politica->markVector[politica->listBuff[1]]){
            return politica->addBuffer[1];
        }
    }
    for (int i = 0; i < 15; i++){
        if(aux[i] == 1 && boolQuesWait[i] && i !=5 && i != 13){
            return i;
        }
    }
    return -1;

}


struct politica_metodos politicaMetodos ={

    .printNumero = printNumero,
    .signalPolitic = signalPolitic

};

extern void new_politica(politica_o * p_politica)
{
   p_politica->numero = 2;
    // rdp_o *rdp;
    // int *listBuff = pn.getIsBuffer();
    // int *addBuffer = pn.getCountBuffer;
    int *markVector;
    int buffer1, buffer2;
    
   p_politica->metodos = &politicaMetodos;
}


