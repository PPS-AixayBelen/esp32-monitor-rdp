#include "cpuProcess.h"
#include <stdio.h>
#include <unistd.h>



void *run(cpuProcess_o *cpuProcess){
    
    int shootResult = 0;
    while(1){
        for (int i = 0; i < (cpuProcess->processNum); i++){
            printf("iteracion %d\n", i);
            shootResult = cpuProcess->monitor->metodos->shoot(cpuProcess->monitor, cpuProcess->processList[i]);
            printf("shootResult - %d\n", shootResult);
            // shootResult = monitor.shoot(cpuProcess->processList[i]);
            if(shootResult == -1){
                printf("END: %d", i);
                return NULL;           
            }
            else if (shootResult > 0){
                sleep(shootResult + 1 );
                cpuProcess->monitor->metodos->shoot(cpuProcess->monitor, cpuProcess->processList[i]);
                // monitor.shoot(cpuProcess->processList[i]);
            }
            else{
            }
        }
    }
}

struct cpuProcess_metodos cpuMetodos ={
    .run = run
};

extern void new_cpuProcess(cpuProcess_o * p_cpuProcess, int *processList, int processNum, monitor_o *monitor)
{
    p_cpuProcess->monitor = monitor;
    p_cpuProcess->processNum = processNum;
    p_cpuProcess->metodos = &cpuMetodos;
    p_cpuProcess->processList = processList;

}


