
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

// #include "monitor.h"
#include "cpuProcess.h"
#include <string.h>
#include "leerMatriz.h"

int main(){

    pthread_attr_t atrib;
    pthread_t c[3];

    pthread_attr_init(&atrib);
    pthread_attr_setscope(&atrib, PTHREAD_SCOPE_SYSTEM);


    pthread_attr_setschedpolicy(&atrib, SCHED_OTHER);
    monitor_o mymonitor;
    rdp_o rdp;
    pthread_attr_setscope(&atrib, PTHREAD_SCOPE_SYSTEM);

    monitor_o *monitor = &mymonitor;
    cpuProcess_o tShooter[3];
    // cpuProcess_o t0Shooter;
    // cpuProcess_o t1Shooter;
    // cpuProcess_o t8Shooter;

    int *shootArray[3];
    int shootSequence1[1]={0}; //dispara T0
    int shootSequence2[1]={5}; //dispara T1
    int shootSequence3[1]={13}; //dispara T8

    shootArray [0] = shootSequence1;
    shootArray [1] = shootSequence2;
    shootArray [2] = shootSequence3;
     
    pthread_mutex_t mutex; 
    pthread_cond_t espera[15];
    int boolQuesWait[15] = {0};

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 15; i++){
        pthread_cond_init(&espera[i], NULL);

    }
    new_rdp(&rdp);
    new_monitor(&mymonitor, mutex, espera, 15, boolQuesWait, &rdp);

    new_cpuProcess(&tShooter[0],shootSequence1, 1, monitor);
    new_cpuProcess(&tShooter[1],shootSequence2, 1, monitor);
    new_cpuProcess(&tShooter[2],shootSequence3, 1, monitor);

    // monitor->metodos->shoot(monitor, 0);
    // monitor->metodos->shoot(monitor, 5);
    for (int i = 0; i < 3; i++)
        pthread_create(&c[i], &atrib,(&tShooter[i])->metodos->run((&tShooter[i])) , (cpuProcess_o *) &tShooter[i]);


    // pthread_create(&c[0], &atrib, (&t0Shooter)->metodos->run((&t0Shooter)) , (cpuProcess_o *) &t0Shooter);
    // printf("voy a crear el proximo hilo\n");
    // pthread_create(&c[1], &atrib, (&t1Shooter)->metodos->run((&t1Shooter)) , (cpuProcess_o *) &t1Shooter);
    // pthread_create(&c[2], &atrib, (&t8Shooter)->metodos->run((&t8Shooter)) , (cpuProcess_o *) &t8Shooter);

    for (int i = 0; i < 3; i++){
        pthread_join(c[i], NULL);
    }
    printf("TERMINEEEEEE\n");

}

