#include "cpuProcess.h"
#include <stdio.h>

void printNumero(cpuProcess_o * cpuProcess){
    printf("Numero: %d \n",cpuProcess->numero);
}

void run(cpuProcess_o * cpuProcess){
    
    printf("holi\n");
    for (int i=0; i < 3; i++){
        printf("%d\n", cpuProcess->processList[i]);
    }
}

struct cpuProcess_metodos cpuMetodos ={

    .printNumero = printNumero,
    .run = run
};

extern void new_cpuProcess(cpuProcess_o * p_cpuProcess, int *processList)
{
    p_cpuProcess->numero = 2;
    p_cpuProcess->metodos = &cpuMetodos;
    p_cpuProcess->processList = processList;

}


