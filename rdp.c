#include "rdp.h"
#include <stdio.h>
#include "leerMatriz.h"

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
    //  .getMarkVector = getMarkVector,
    //  .getUseBuffer = getUseBuffer,
    //  .getIsBuffer = getIsBuffer,
    //  .getCountBuffer = getCountBuffer,
     //getSensitized = getSensitized,
    // .ifEnd = ifEnd
};

extern void new_rdp(rdp_o * p_rdp)
{
    p_rdp->estados=16;
    p_rdp->transiciones = 15;
    p_rdp->minTimeArrival = 15;
    p_rdp->minTimeSrv1 = 50;
    p_rdp->minTimesSrv2 = 50;

    for (int i = 0;i<p_rdp->transiciones;i++)
    {
        p_rdp->B[i] = 0;
        p_rdp->E[i] = 0;
    }

    leer_matriz(16,15,p_rdp->Ineg[0],"Ineg");
    leer_matriz(16,15,p_rdp->Ipos[0],"Ipos");
    leer_matriz(16,15,p_rdp->I[0],"Imatriz");
    leer_matriz(16,15,p_rdp->H[0],"H");

    // for(int i = 0;i<16;i++){
    // for(int j = 0; j<15;j++){
    //     printf("%d ",p_rdp->Ineg[i][j]);
    // }
    // printf("\n");
    // }
  

   p_rdp->numero = 2;
   p_rdp->metodos = &rdpMetodos;
}





