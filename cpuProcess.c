#include "cpuProcess.h"
#include <stdio.h>
#include <unistd.h>

void *run(cpuProcess_o *cpuProcess)
{
    printf("VOY A DISPARAR: %d\n", cpuProcess->processList[0]);
    sleep(3);
    int shootResult = 0;
    while (1)
    {
        for (int i = 0; i < (cpuProcess->processNum); i++)
        {
            printf("Nro de transicion a disparar: %d\n", cpuProcess->processList[i]);
            shootResult = cpuProcess->monitor->metodos->shoot(cpuProcess->monitor, cpuProcess->processList[i]);
            printf("shootResult - %d disparo- %d\n", shootResult, cpuProcess->processList[i]);
            // shootResult = monitor.shoot(cpuProcess->processList[i]);
            if (shootResult == -1)
            {
                printf("END: %d", i);
                return NULL;
            }
            else if (shootResult > 0)
            {
                printf("me falta tiempo para sensibilizarme\n");
                sleep(shootResult + 1);
                cpuProcess->monitor->metodos->shoot(cpuProcess->monitor, cpuProcess->processList[i]);
                // monitor.shoot(cpuProcess->processList[i]);
            }
            else
            {
            }
        }
    }
}

struct cpuProcess_metodos cpuMetodos = {
    .run = run};

extern void new_cpuProcess(cpuProcess_o *p_cpuProcess, int *processList, int processNum, monitor_o *monitor)
{
    p_cpuProcess->monitor = monitor;
    p_cpuProcess->processNum = processNum;
    p_cpuProcess->metodos = &cpuMetodos;
    p_cpuProcess->processList = processList;
}
