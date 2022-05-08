
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

// #include "monitor.h"
#include "cpuProcess.h"
#include <string.h>
#include "leerMatriz.h"

int main(){

    pthread_attr_t atrib;
    pthread_t c[1];
    pthread_attr_init(&atrib);

    monitor_o mymonitor;
    rdp_o rdp;
    pthread_attr_setscope(&atrib, PTHREAD_SCOPE_SYSTEM);

    monitor_o *monitor = &mymonitor;

    cpuProcess_o myCpuProcess;
    int array[2]={0,5};

    pthread_mutex_t mutex; 
    pthread_cond_t espera[15];
    int boolQuesWait[15] = {0};

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 15; i++){
        pthread_cond_init(&espera[i], NULL);

    }
    new_rdp(&rdp);
    new_monitor(&mymonitor, mutex, espera, 15, boolQuesWait, &rdp);
    new_cpuProcess(&myCpuProcess,array, 2, monitor);
    cpuProcess_o *cpuProcess = &myCpuProcess; 

    // monitor->metodos->shoot(monitor, 0);
    // monitor->metodos->shoot(monitor, 5);
    pthread_create(&c[0], &atrib, cpuProcess->metodos->run(cpuProcess) , (cpuProcess_o *) &myCpuProcess);
    pthread_join(c[0], NULL);
    printf("TERMINEEEEEE\n");

}

