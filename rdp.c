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

//     int Ineg[][] = {
// //               Ar P  P2 S  S2 1  12 13 14 2  5  6  7  8  9
//                 {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // M0=Active
//                 {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // M1=Active_2
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},    // M2=CPU_buffer
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},    // M3=CPU_buffer2
//                 {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},    // M4=CPU_ON
//                 {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},    // M5=CPU_ON_2
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},    // M6=Idle
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},    // M7=Idle_2
//                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    // M8=P0
//                 {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},    // M9=P1
//                 {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},    // M10=P13
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},    // M11=P6
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},    // M12=Power_up
//                 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},    // M13=Power_up_2
//                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},    // M14=Stand_by
//                 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},    // M15=Stand_by_2

//         };















   p_rdp->numero = 2;
   p_rdp->metodos = &rdpMetodos;
}





