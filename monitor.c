#include "monitor.h"

#include <stdio.h>
#include <stdlib.h>

void finalSignalPolitic (monitor_o *monitor){
 
     for (int i = 0; i < (monitor->numberTransitions); i++) {
        pthread_cond_signal(&(monitor->espera[i]));     
        monitor->boolQuesWait[i] = 0;
    }

}



int verifyMInvariants (monitor_o *monitor){

    int mark[16];

    for (int i = 0; i < 16; i++){
        mark[i] = monitor->rdp->M[i];
    }

    if (((mark[1] + mark[7]) == 1) && ((mark[4] + mark[12] + mark[14]) == 1) && ((mark[5] + mark[13] + mark[15]) == 1) && ((mark[0] + mark[6]) == 1) && ((mark[8] + mark[9]) == 1))
    {
         return 1;
    }   
    else 
        return 0;

}


void signalPoliticMonitor (monitor_o *monitor){

    int t = monitor->politica->metodos->signalPolitic(monitor->politica, monitor->boolQuesWait); // Devuelve el indice de la transicion donde esta el hilo a despertar
     if (t != -1) {
        pthread_cond_signal(&(monitor->espera[t]));
        return;
     }

    if (monitor->rdp->metodos->ifEnd(monitor->rdp) ) { // Si la politica devuelve -1 es porque no pudo despertar a nadie, me fijo si tengo que terminar
        if(DEBUG)
            printf("No se pudo despertar a ningun hilo\n");
        monitor->end=1;
        for (int i = 0; i < 15; i++){
            pthread_cond_broadcast(&(monitor->espera[i]));
        }

        finalSignalPolitic(monitor);
    }
        
    return;

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
            if(DEBUG)
                printf("me fui a dormir disparando %d, con shootResult = %d\n", index, shootResult);
            monitor->boolQuesWait[index] = 1;
            pthread_cond_wait(&(monitor->espera[index]), &(monitor->mutex));
        }
        else if (shootResult == 0){
                
            monitor->boolQuesWait[index] = 0;
            signalPoliticMonitor(monitor);
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

    .verifyMInvariants = verifyMInvariants,
    .signalPoliticMonitor = signalPoliticMonitor,
    .finalSignalPolitic = finalSignalPolitic,
    .shoot = shoot
};

extern void new_monitor(monitor_o * p_monitor, pthread_mutex_t mutex, pthread_cond_t *espera, int numberTransitions, int *boolQuesWait, rdp_o *rdp)
{
    p_monitor->rdp = rdp;
    p_monitor->mutex = mutex;
    p_monitor->espera = espera;
    p_monitor->numberTransitions = numberTransitions;
    p_monitor->boolQuesWait = boolQuesWait;
    p_monitor->end = 0;
    p_monitor->metodos = &monitorMetodos;
    p_monitor->politica = (politica_o *)malloc(sizeof(politica_o));
    new_politica(p_monitor->politica, rdp);
}

