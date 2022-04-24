#include "rdp.h"
#include <stdio.h>

void printNumero(rdp_o * rdp){
    printf("Numero: %d \n",rdp->numero);
}

int isPos (rdp_o * rdp,int index){
    return 0;
}


struct rdp_metodos rdpMetodos ={

    .printNumero = printNumero,
    .isPos = isPos,
    // .updateTimeStamps = updateTimeStamps,
    // .getMarkVector = getMarkVector,
    // .getUseBuffer = getUseBuffer,
    // .getIsBuffer = getIsBuffer,
    // .getCountBuffer = getCountBuffer,
    // .getSensitized = getSensitized,
    // .ifEnd = ifEnd
};

extern void new_rdp(rdp_o * p_rdp)
{
   p_rdp->numero = 2;
   p_rdp->metodos = &rdpMetodos;
}


