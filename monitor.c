#include "monitor.h"

#include <stdio.h>
#include <stdlib.h>

void logInvariantePlaza(int *vectorMarcado, int size)
{
    FILE *invPlaza = fopen("./test/InvariantesPlaza", "a+");

    for (int i = 0; i < size; i++)
    {
        fprintf(invPlaza, "%d ", vectorMarcado[i]);
    }
    fputs("\n", invPlaza);
    fclose(invPlaza);
}

void logInvarianteTransicion(int index)
{
    char *transicion[] =  {"T0", "T4", "T11", "T3", "T10", "TA", "T12", "T13", "T14", "T2", "T5", "T6", "T7", "T8", "T9"};
    FILE * file = fopen("./test/InvariantesTransicion", "a+");

    fputs(transicion[index],file);
    fclose(file);

}

void finalSignalPolitic(monitor_o *monitor)
{

    for (int i = 0; i < (monitor->numberTransitions); i++)
    {
        //     quesWait.get (i).signal ();
        pthread_cond_signal(&(monitor->espera[i]));
        monitor->boolQuesWait[i] = 0;
    }
}

void printArray2(int size, int *array)
{
    printf("{ ");
    for (int i; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("}\n");
}

void signalPoliticMonitor(monitor_o *monitor)
{

    int t = monitor->politica->metodos->signalPolitic(monitor->politica, monitor->boolQuesWait); // Devuelve el indice de la transicion donde esta el hilo a despertar
    if (t != -1)
    {
        //     quesWait.get (t).signal ();
        pthread_cond_signal(&(monitor->espera[t]));
        return;
    }

    if (monitor->rdp->metodos->ifEnd(monitor->rdp))
    { // Si la politica devuelve -1 es porque no pudo despertar a nadie, me fijo si tengo que terminar
        printf("LA POLITICA DEVOLVIO -1\n");
        monitor->end = 1;
        for (int i = 0; i < 15; i++)
        {
            pthread_cond_broadcast(&(monitor->espera[i]));
        }

        finalSignalPolitic(monitor);
    }

    return;
}

int shoot(monitor_o *monitor, int index)
{

    pthread_mutex_lock(&(monitor->mutex));

    int numberTransitions = monitor->numberTransitions;
    int shoot[numberTransitions];
    for (int i = 0; i < monitor->numberTransitions; i++)
    {
        shoot[i] = 0;
    }
    shoot[index] = 1;
    int shootResult = -1;

    while (1)
    {
        shootResult = monitor->rdp->metodos->isPos(monitor->rdp, shoot);

        if (shootResult < 0)
        {
            if (monitor->end)
            {
                pthread_mutex_unlock(&(monitor->mutex));
                return -1;
            }
            printf("me fui a mimir disparando %d, por shootResult = %d\n", index, shootResult);
            monitor->boolQuesWait[index] = 1;
            pthread_cond_wait(&(monitor->espera[index]), &(monitor->mutex));
        }
        else if (shootResult == 0)
        {
            logInvariantePlaza(&monitor->rdp->M[0],monitor->rdp->estados);
            logInvarianteTransicion(index);
            monitor->boolQuesWait[index] = 0;
            signalPoliticMonitor(monitor);
            break;
        }
        else
        {
            pthread_mutex_unlock(&(monitor->mutex));
            return shootResult;
        }
    }

    pthread_mutex_unlock(&(monitor->mutex));
    return 0;
}

struct monitor_metodos monitorMetodos = {

    .signalPoliticMonitor = signalPoliticMonitor,
    .finalSignalPolitic = finalSignalPolitic,
    .shoot = shoot};

extern void new_monitor(monitor_o *p_monitor, pthread_mutex_t mutex, pthread_cond_t *espera, int numberTransitions, int *boolQuesWait, rdp_o *rdp)
{
    p_monitor->rdp = rdp;
    p_monitor->mutex = mutex;
    p_monitor->espera = espera;
    p_monitor->numberTransitions = numberTransitions;
    p_monitor->boolQuesWait = boolQuesWait;
    p_monitor->end = 0;
    p_monitor->metodos = &monitorMetodos;
    p_monitor->politica = (politica_o *)malloc(sizeof(politica_o));
    new_politica(p_monitor->politica, rdp);
}
