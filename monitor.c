#include "monitor.h"
#include <stdio.h>

void printNumero(monitor_o * monitor){
    printf("Numero: %d \n",monitor->numero);
}


void initConditions (monitor_o * monitor){
    printf("dummy print\n");
}


char *getTransitions (monitor_o *monitor){
    printf("dummy print\n");
}


int verifyMInvariants (monitor_o *monitor){
    printf("dummy print\n");
}


void signalPolitic (monitor_o *monitor){
    printf("dummy print\n");
}


void finalSignalPolitic (monitor_o *monitor){
    printf("dummy print\n");
}


void showBoolQueuesWait (monitor_o *monitor){
    printf("dummy print\n");
}


int shoot (monitor_o *monitor, int index){
    printf("dummy print\n");
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

