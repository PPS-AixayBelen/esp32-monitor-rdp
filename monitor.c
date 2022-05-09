#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>

void printNumero(monitor_o * monitor){
    printf("Numero: %d \n",monitor->numero);
}

void printArray2(int size, int *array)
{
    printf("{ ");
    for (int i; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("}\n");
}

int verifyMInvariants (monitor_o *monitor){

    int mark[16];
    printf("Vector de Marcado nuevo\n");
    printArray2(16, monitor->rdp->M);

    for (int i = 0; i < 16; i++){
        mark[i] = monitor->rdp->M[i];
    }

    if (((mark[1] + mark[7]) == 1) && ((mark[4] + mark[12] + mark[14]) == 1) && ((mark[5] + mark[13] + mark[15]) == 1) && ((mark[0] + mark[6]) == 1) && ((mark[8] + mark[9]) == 1))
    {
         return 1;
    }   
    else 
        return 0; //rompiose        

}


void signalPolitic (monitor_o *monitor){

    // int t = 0;
    // // int t = politica.signalPolitic (boolQuesWait); // Devuelve el indice de la transicion donde esta el hilo a despertar
    //  if (t != -1) {
    // //     quesWait.get (t).signal (); 
    //         pthread_cond_signal(&(monitor->espera[t]));
    //      return;
    //  }

    // if (pn.ifEnd ()) { // Si la politica devuelve -1 es porque no pudo despertar a nadie, me fijo si tengo que terminar
    //     end = true;
    //     if (printDebug) System.out.println ("I'm final boss, bro");
    //     finalSignalPoliticV2 ();
    // }
        
    return;

}


void finalSignalPolitic (monitor_o *monitor){
 
     for (int i = 0; i < (monitor->numberTransitions); i++) {
    //     quesWait.get (i).signal ();
        pthread_cond_signal(&(monitor->espera[i]));     
        monitor->boolQuesWait[i] = 0;
    }

}



int shoot (monitor_o *monitor, int index){

    pthread_mutex_lock(&(monitor->mutex));
    
    int numberTransitions = monitor->numberTransitions;
    int shoot [numberTransitions];
    for (int i = 0; i < monitor->numberTransitions; i++){
        shoot[i] = 0;
    }
    shoot[index] = 1;
    int shootResult = -1;


    while(1){

        shootResult = monitor->rdp->metodos->isPos(monitor->rdp, shoot);
        
        
        if (shootResult < 0){
            if (monitor->end){
                pthread_mutex_unlock(&(monitor->mutex));
                return -1;
            }
            printf("me fui a mimir disparando %d, por shootResult = %d\n", index, shootResult);
            monitor->boolQuesWait[index] = 1;
            pthread_cond_wait(&(monitor->espera[index]), &(monitor->mutex));
        }
        else if (shootResult == 0){
                
            monitor->boolQuesWait[index] = 0;
            //signalPolitic(monitor);
            break;
        }
        else{
            pthread_mutex_unlock(&(monitor->mutex));
            return shootResult;
        }

    }

    if( verifyMInvariants(monitor) ){
        pthread_mutex_unlock(&(monitor->mutex));
        return 0;
    }
    else{
        printf("error de Invariantes\n");
        exit(1); //rompiose
    }

    pthread_mutex_unlock(&(monitor->mutex));
    return -1;
    
}


struct monitor_metodos monitorMetodos ={

    .printNumero = printNumero,
    .verifyMInvariants = verifyMInvariants,
    .signalPolitic = signalPolitic,
    .finalSignalPolitic = finalSignalPolitic,
    .shoot = shoot
};

extern void new_monitor(monitor_o * p_monitor, pthread_mutex_t mutex, pthread_cond_t *espera, int numberTransitions, int *boolQuesWait, rdp_o *rdp)
{
    p_monitor->rdp = rdp;
    p_monitor->numero = 2;
    p_monitor->mutex = mutex;
    p_monitor->espera = espera;
    p_monitor->numberTransitions = numberTransitions;
    p_monitor->boolQuesWait = boolQuesWait;
    p_monitor->end = 0;
    p_monitor->metodos = &monitorMetodos;
}

