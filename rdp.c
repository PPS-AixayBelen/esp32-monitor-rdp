#include "rdp.h"
#include "leerMatriz.h"
#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print = 1;

int isPos(rdp_o *rdp, int *index);
void updateTimeStamps(rdp_o *rdp, int *oldSens);
void getSensitized(rdp_o *rdp);
int ifEnd(rdp_o *rdp);
void printArray(int size, int *array);
void logInvariantePlaza(int *vectorMarcado, int size);

struct rdp_metodos rdpMetodos = {

    .isPos = isPos,
    .updateTimeStamps = updateTimeStamps,
    .getSensitized = getSensitized,
    .ifEnd = ifEnd};

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

extern void new_rdp(rdp_o *p_rdp)
{
    p_rdp->estados = 16;
    p_rdp->transiciones = 15;
    p_rdp->minTimeArrival = 4;
    p_rdp->minTimeSrv1 = 1;
    p_rdp->minTimeSrv2 = 1;
    p_rdp->dataNumber = 3;
    p_rdp->packetCounter = 0;

    for (int i = 0; i < p_rdp->transiciones; i++)
    {
        p_rdp->B[i] = 0;
        p_rdp->E[i] = 0;
    }

    char M[] = "0 0 0 0 0 0 1 1 1 0 0 0 0 0 1 1";
    cargar_vector(16, p_rdp->M, M);
    leer_matriz(16, 15, p_rdp->Ineg[0], "Ineg");
    leer_matriz(16, 15, p_rdp->Ipos[0], "Ipos");
    leer_matriz(16, 15, p_rdp->I[0], "Imatriz");
    leer_matriz(16, 15, p_rdp->H[0], "H");

    // for(int i = 0;i<16;i++){
    // for(int j = 0; j<15;j++){
    //     printf("%d ",p_rdp->Ineg[i][j]);
    // }
    // printf("\n");
    // }

    char userBuffer[] = "5 13 9 14";
    cargar_vector(4, p_rdp->useBuffers, userBuffer);

    char isBuffer[] = "2 3";
    cargar_vector(2, p_rdp->isBuffer, isBuffer);

    p_rdp->isGenTransition[0] = 0;

    char isAddBuffer[] = "5 13";
    cargar_vector(2, p_rdp->isAddBuffer, isAddBuffer);

    for (int i = 0; i < 15; i++)
    {
        time(&p_rdp->sensitizedTime[i]);
    }

    p_rdp->metodos = &rdpMetodos;
}

int isPos(rdp_o *rdp, int *index)
{
    char *M_name[] = {"Active", "Active_2", "CPU_buffer", "CPU_buffer 2", "CPU_ON", "CPU_ON_2", "Idle", "Idle_2", "P0", "P1", "P13", "P6", "Power_up", "Power_up_2", "Stand_by", "Stand_by_2"};

    for (int m = 0; m < rdp->transiciones; m++)
    {
        rdp->E[m] = 1;

        for (int n = 0; n < rdp->estados; n++)
        {
            if (rdp->M[n] - rdp->Ineg[n][m] < 0)
            {
                rdp->E[m] = 0;
                break;
            }
        }
    }

    // Esto para que era?
    if (rdp->packetCounter == rdp->dataNumber)
        rdp->E[0] = 0;

    if (rdp->M[2] >= 10)
        rdp->E[5] = 0;

    if (rdp->M[3] >= 10) // Limite buffer 2
        rdp->E[13] = 0;

    int temp;

    rdp->metodos->getSensitized(rdp);
    int aux[rdp->transiciones];

    for (int i = 0; i < rdp->transiciones; i++)
    {
        aux[i] = rdp->Sensitized[i];
    }

    int oldSens[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // se usa despues para actualizar timestamps

    for (int i = 0; i < rdp->transiciones; i++)
    {
        oldSens[i] = aux[i];
    }

    for (int m = 0; m < rdp->transiciones; m++)
    {
        if (aux[m] * index[m] > 0)
            aux[m] = 1; // sigma and Ex
        else
            aux[m] = 0; // Si no pongo el else, quedan los unos de la operacion anterior
    }

    int zeroCounter = 0; // Esto es para ver que lo que quiero y puedo disparar sea diferente de 0
    for (int m = 0; m < rdp->transiciones; m++)
    {
        if (aux[m] != 0)
            zeroCounter++;
    }
    if (zeroCounter == 0)
    {
        printf("vector de disparo vacio o insensibilizado\n");
        return -1;
    }

    int aux2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int n = 0; n < rdp->estados; n++)
    {
        for (int m = 0; m < rdp->transiciones; m++)
        {
            temp = rdp->I[n][m] * aux[m];
            aux2[n] = aux2[n] + temp;
        }
    }

    int mPrima[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (print)
        printf("Nuevo marcado: \n");
    for (int n = 0; n < rdp->estados; n++)
    {                                    // Si algun numero del nuevo vector de marcado es negativo, no puedo dispararla
        mPrima[n] = rdp->M[n] + aux2[n]; // Sumo para obtener el nuevo vector de marcado
        if (print)
            printf("%d %s \n", mPrima[n], M_name[n]);

        if (mPrima[n] < 0)
        {
            printf("la transicion no se puede disparar, marcado resultante\n");
            return -1;
        }
    }

    time_t shootTime;

    time(&shootTime);

    time_t transitionTime = 0;

    for (int i = 0; i < rdp->transiciones; i++)
    {
        if (index[i] > 0)
        {
            if (i == 0 || i == 3 || i == 4)
            {
                switch (i)
                {
                case 0: // TODO: Esto tiene sentido?
                    transitionTime = rdp->sensitizedTime[i] + rdp->minTimeArrival;
                    break;
                case 3:
                    transitionTime = rdp->sensitizedTime[i] + rdp->minTimeSrv1;
                    break;
                case 4:
                    transitionTime = rdp->sensitizedTime[i] + rdp->minTimeSrv2;
                    break;
                }
                // TODO: MIRAAAAAR
                if ((shootTime > transitionTime) || (shootTime == transitionTime))
                {                                  // si el tiempo actual es mayor que el de sensibilizado + minTime
                    time(&rdp->sensitizedTime[i]); // actualizo el tiempo de sensibilizado "para que vuelva a 0" (?
                }
                else
                {
                    if (print)
                        printf("%s %d %s\n", "Quise disparar T", i, " y estoy fuera del intervalo de tiempo");
                    return (unsigned int)transitionTime - shootTime;
                }
            }
        }
    }
    char *number;
    for (int i = 0; i < rdp->estados; i++)
    {
        rdp->M[i] = mPrima[i];
    }

    logInvariantePlaza(&mPrima[0], rdp->estados);

    // printf("Array de marcado\n");
    // printArray(16, rdp->M);
    if (index[0] == 1)
    {
        rdp->packetCounter = rdp->packetCounter + 1;
        printf("\n\n Nuevo paquete ahora tengo: %d\n\n", rdp->packetCounter);
    }

    updateTimeStamps(rdp, oldSens); // Le mando el vector de sensiblizado del marcado anterior

    return 0;
}

void updateTimeStamps(rdp_o *rdp, int *oldSens)
{
    for (int m = 0; m < rdp->transiciones; m++)
    {
        rdp->E[m] = 1;

        for (int n = 0; n < rdp->estados; n++)
        {
            if (rdp->M[n] - rdp->Ineg[n][m] < 0)
            {
                rdp->E[m] = 0;
                break;
            }
        }
    }

    // Limitacion de generacion de datos (T0)
    if (rdp->packetCounter == rdp->dataNumber)
        rdp->E[0] = 0;
    if (rdp->M[2] >= 10)
        rdp->E[5] = 0;
    if (rdp->M[3] >= 10)
        rdp->E[13] = 0;

    rdp->metodos->getSensitized(rdp);

    int newSens[rdp->transiciones];

    for (int i = 0; i < rdp->transiciones; i++)
    {
        newSens[i] = rdp->Sensitized[i];
    }

    // if (print)
    // {
    //     printf("Viejo sensiblizado: ");
    //     printArray(rdp->transiciones, oldSens);
    //     printf("Nuevo sensiblizado: ");
    //     printArray(rdp->transiciones, newSens);
    // }

    // printf("MATRIZ DE TRANSICIONES SENSIBILIZADAS\n");
    // printArray(rdp->transiciones, newSens);
    for (int i = 0; i < rdp->transiciones; i++)
    {
        if ((newSens[i] > 0) && (newSens[i] != oldSens[i]))
        {
            time(&rdp->sensitizedTime[i]);
        }
    }
}

void printArray(int size, int *array)
{
    printf("{ ");
    for (int i; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("}\n");
}

void getSensitized(rdp_o *rdp)
{
    int temp;

    int aux[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Calculo B (vector de desensibilizado)
    for (int m = 0; m < rdp->transiciones; m++)
    {
        rdp->B[m] = 0;
        for (int n = 0; n < rdp->estados; n++)
        { // Si algun numero del nuevo vector de marcado es = 1, no puedo dispararla
            // temp = H[m][i] * Q[i];    // Sumo para obtener el nuevo vector de desensibilizado
            temp = rdp->H[m][n] * rdp->M[n];
            rdp->B[m] = rdp->B[m] + temp; // B = 1 -> no se puede :(
        }
        if (rdp->B[m] == 0)
        { // B negado
            rdp->B[m] = 1;
        }
        else
        {
            rdp->B[m] = 0;
        }
    }

    for (int m = 0; m < rdp->transiciones; m++)
    {
        if (rdp->B[m] * rdp->E[m] > 0)
            aux[m] = 1; // B and E
        else
            aux[m] = 0; // Si no pongo el else, quedan los unos de la operacion anterior
    }

    for (int i = 0; i < rdp->transiciones; i++)
    {
        rdp->Sensitized[i] = aux[i];
    }
}

int ifEnd(rdp_o *rdp)
{
    int Minitial[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1};
    for (int n = 0; n < rdp->estados; n++)
    {
        if (rdp->M[n] != Minitial[n])
            return 0;
    }
    if (rdp->packetCounter == rdp->dataNumber)
    {
        return 1;
    }
    return 0;
}
