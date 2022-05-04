
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

#include <stdio.h>
#include "monitor.h"
#include "rdp.h"
#include <stdlib.h>
#include <string.h>
#include "leerMatriz.h"

int main(){

monitor_o mymonitor;

new_monitor(&mymonitor);

mymonitor.metodos->printNumero(&mymonitor);
}

