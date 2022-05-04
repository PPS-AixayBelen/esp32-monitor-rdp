
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

#include "monitor.h"
#include <string.h>
#include "leerMatriz.h"

int main(){

monitor_o mymonitor;
rdp_o rdp;

monitor_o *monitor = &mymonitor;


pthread_mutex_t mutex; 
pthread_cond_t espera[15];
int boolQuesWait[15] = {0};

new_rdp(&rdp);
new_monitor(&mymonitor, mutex, espera, 15, boolQuesWait, &rdp);

monitor->metodos->shoot(monitor, 0);

}

