#include <stdio.h>
#include "monitor.h"


int main(){

monitor_o mymonitor;

new_monitor(&mymonitor);

mymonitor.metodos->printNumero(&mymonitor);

}