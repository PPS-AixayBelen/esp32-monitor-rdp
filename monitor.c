#include "monitor.h"
#include <stdio.h>

void printNumero(monitor_o * monitor){
    printf("Numero: %d \n",monitor->numero);
}


void initConditions (monitor_o * monitor){ //podriamos no poner esta funcion, si solo inicializa a 0 todo el array

    for (int i = 0; i > monitor->numberTransitions; i++){
        monitor->boolQuesWait[i] = 0;
        // quesWait.add (lock.newCondition ());

    }

    // politica = new Politica (pn);

}


char *getTransitions (monitor_o *monitor){ //creo que esta funcion la usabamos para el log, ya no seria necesaria
        return monitor->transitions;
}


int verifyMInvariants (monitor_o *monitor){

    // int *mark = pn.getMarkVector();
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


void showBoolQueuesWait (monitor_o *monitor){ //funcion para debug, tampoco es necesaria


    printf("Dummy print \n");

    // int aux[] = pn.getSensitized ();
    // int count = 0;
    //     for (boolean item : boolQuesWait) {
    //         if (printDebug) System.out.println ("index:" + count + "    " + item + "  ---   " + aux[count]);
    //         count++;
    //     }
    //     if (printDebug)
    //         System.out.println ("--------------------------------- 0 --------------------------------------------");
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
    .initConditions = initConditions,
    .getTransitions = getTransitions,
    .verifyMInvariants = verifyMInvariants,
    .signalPolitic = signalPolitic,
    .finalSignalPolitic = finalSignalPolitic,
    .showBoolQueuesWait = showBoolQueuesWait,
    .shoot = shoot
};

extern void new_monitor(monitor_o * p_monitor)
{
    p_monitor->numero = 2;
    p_monitor->numberTransitions = 15;
    int boolQuesWait[p_monitor->numberTransitions];
    p_monitor->boolQuesWait = boolQuesWait;
    p_monitor->end = 0;
    p_monitor->transitions = "";
    p_monitor->metodos = &monitorMetodos;
}

