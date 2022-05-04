#include "monitor.h"
#include <stdio.h>

void printNumero(monitor_o * monitor){
    printf("Numero: %d \n",monitor->numero);
}



int verifyMInvariants (monitor_o *monitor){

    // int *mark = pn.getMarkVector();
    int mark [15];
    if (((mark[1] + mark[7]) == 1) && ((mark[4] + mark[12] + mark[14]) == 1) && ((mark[5] + mark[13] + mark[15]) == 1) && ((mark[0] + mark[6]) == 1) && ((mark[8] + mark[9]) == 1))
        return 0;
    else 
        return 1; //rompiose        

}


void signalPolitic (monitor_o *monitor){

    int t = 0;
    // int t = politica.signalPolitic (boolQuesWait); // Devuelve el indice de la transicion donde esta el hilo a despertar
     if (t != -1) {
    //     quesWait.get (t).signal (); 
            pthread_cond_signal(&(monitor->espera[t]));
         return;
     }

    // if (pn.ifEnd ()) { // Si la politica devuelve -1 es porque no pudo despertar a nadie, me fijo si tengo que terminar
    //     end = true;
    //     if (printDebug) System.out.println ("I'm final boss, bro");
    //     finalSignalPoliticV2 ();
    // }
        

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
    shoot[index] = 1;
    int shootResult = -1;

    while(1){

        //shootResult = pn.isPos(shoot);
        if (shootResult < 0){
            if (monitor->end){

                pthread_mutex_unlock(&(monitor->mutex));
                return -1;
            }
            monitor->boolQuesWait[index] = 1;
            pthread_cond_wait(&(monitor->espera[index]), &(monitor->mutex));
        }
        else if (shootResult == 0){
            monitor->boolQuesWait[index] = 0;
            signalPolitic(monitor);
            break;
        }
        else{
            
            pthread_mutex_unlock(&(monitor->mutex));
            return shootResult;

        }

    }

    if( verifyMInvariants(monitor) ){
        pthread_mutex_unlock(&(monitor->mutex));
    }
    else{
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

extern void new_monitor(monitor_o * p_monitor, pthread_mutex_t mutex, pthread_cond_t *espera, int numberTransitions, int *boolQuesWait)
{
    p_monitor->numero = 2;
    p_monitor->mutex = mutex;
    p_monitor->espera = espera;
    p_monitor->numberTransitions = numberTransitions;
    p_monitor->boolQuesWait = boolQuesWait;
    p_monitor->end = 0;
    p_monitor->metodos = &monitorMetodos;
}
