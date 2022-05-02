#include "rdp.h"
#include <stdio.h>
#include "leerMatriz.h"


int isPos (rdp_o * rdp,int index){
    return 0;
}


struct rdp_metodos rdpMetodos ={

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

    p_rdp->minTimeArrival = 25;
    p_rdp->minTimeSrv1 = 50;
    p_rdp->minTimesSrv2 = 50;
    p_rdp->estados = 16;
    p_rdp-> transiciones = 15;

    char M[] = "0 0 0 0 0 0 1 1 1 0 0 0 0 0 1 1";
    cargar_vector(16,p_rdp->M,M);
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

    char userBuffer[] = "5 13 9 14";
    cargar_vector(4,p_rdp->useBuffers,userBuffer);

    char isBuffer[] = "2 3";
    cargar_vector(2,p_rdp->isBuffer,isBuffer);

   p_rdp->isGenTransition[0]=0;

    char isAddBuffer[] = "5 13";
    cargar_vector(2,p_rdp->isAddBuffer,isAddBuffer);

    //Cargar sensitizedTime

   p_rdp->metodos = &rdpMetodos;
}





