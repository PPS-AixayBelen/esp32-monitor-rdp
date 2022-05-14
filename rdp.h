#ifndef _RDP_
#define _RDP_
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rdp rdp_o;

struct rdp_metodos
{

    int (*isPos)(rdp_o *, int *index);
    void (*updateTimeStamps)(rdp_o *, int *oldSens);
    void (*getSensitized)(rdp_o *);
    int (*ifEnd)(rdp_o *);
};

struct rdp
{

    int M[16]; //
    int B[15];
    int Ipos[16][15]; //
    int Ineg[16][15]; //
    int I[16][15];    //
    int H[15][16];    //
    int E[15];        //
    int Sensitized[15];

    time_t sensitizedTime[15];
    int minTimeArrival;
    int minTimeSrv1;
    int minTimeSrv2;
    int useBuffers[4];
    int isBuffer[2];
    int isGenTransition[1];
    int isAddBuffer[2];

    int estados;
    int transiciones;
    int dataNumber;
    int packetCounter; // Es boolean
    void *invPlaza;

    const struct rdp_metodos *metodos;
};

// Funciones

void new_rdp(rdp_o *p_rdp);

#endif