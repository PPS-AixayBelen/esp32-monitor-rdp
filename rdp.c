#include "rdp.h"
#include <stdio.h>

void printNumero(rdp_o * rdp){
    printf("Numero: %d \n",rdp->numero);
}

struct rdp_metodos rdpMetodos ={

    .printNumero = printNumero
};

extern void new_rdp(rdp_o * p_rdp)
{
   p_rdp->numero = 2;
   p_rdp->metodos = &rdpMetodos;
}
