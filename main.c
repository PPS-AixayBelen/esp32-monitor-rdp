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

