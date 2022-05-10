//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT
#include <pthread.h>
#include "rdp.h"

typedef struct monitor monitor_o;

struct monitor_metodos{

    void (*printNumero) (monitor_o *);
    int (*verifyMInvariants)(monitor_o *);
    void (*signalPolitic)(monitor_o *);
    void (*finalSignalPolitic)(monitor_o *);
    int (*shoot)(monitor_o *, int index);
};

struct monitor{
    
    int numero; //Para probar
    
    int numberTransitions;
    pthread_mutex_t mutex; //reemplaza al reentrant lock
    pthread_cond_t *espera; //reemplazaria al quesWait, tendria que haber una por cada transcion
    int *boolQuesWait; //0 = no esta esperando , 1 = esta esperando
    // Politica politica;
    rdp_o *rdp;
    int end;
    const struct monitor_metodos * metodos;    

};


void new_monitor(monitor_o *p_monitor, pthread_mutex_t mutex,pthread_cond_t *espera, int numberTransitions, int *boolQuesWait, rdp_o *rdp);
