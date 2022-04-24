
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

#include <stdio.h>
#include <pthread.h>

#include "cpuProcess.h"


int main(){

    int i;
    pthread_attr_t atrib;
    pthread_t c[1];

    pthread_attr_init(&atrib);

    //battle royale de hilos por los recursos(?)
    pthread_attr_setscope(&atrib, PTHREAD_SCOPE_SYSTEM);

    //el scheduling es round robin 
    i = pthread_attr_setschedpolicy(&atrib, SCHED_RR);


    cpuProcess_o myCpuProcess;
    int array[3]={1,2,3};

    new_cpuProcess(&myCpuProcess,array);

    myCpuProcess.metodos->printNumero(&myCpuProcess);


    // pthread_mutex_init(&mutex, NULL);
    // //inicializa la cola de condicion donde esperan los hilos que no consiguen el mutex
    // pthread_cond_init(&espera, NULL);

    //inicializa 5 clientes
    // for (i = 0; i < 5; i++)
        pthread_create(&c[i], &atrib, myCpuProcess.metodos->run, (cpuProcess_o *) &myCpuProcess);
        pthread_join(c[i], NULL);

}