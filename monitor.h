
  
//Defining _REENTRANT causes the compiler to use thread safe (i.e. re-entrant) 
//versions of several functions in the C library.
#define _REENTRANT

#include <pthread.h>

typedef struct monitor monitor_o;

struct monitor_metodos{

    void (*printNumero) (monitor_o *);
    void (*initConditions) (monitor_o *);
    char *(*getTransitions) (monitor_o *); //creo que este metodo era para los logs asi que capaz no haria falta
    int (*verifyMInvariants)(monitor_o *);
    void (*signalPolitic)(monitor_o *);
    void (*finalSignalPolitic)(monitor_o *);
    void (*showBoolQueuesWait)(monitor_o *);
    int (*shoot)(monitor_o *, int index);
};

struct monitor{
    
    int numero; //Para probar

    int numberTransitions;
    //revisar como se asocian los mutex a las condiciones (si un mutex se puede asociar a mas de una condicion, por ej)
    pthread_mutex_t mutex; //reemplaza al reentrant lock
    pthread_cond_t *espera; //reemplazaria al quesWait, tendria que haber una por cada transcion
    int *boolQuesWait; //0 = no esta esperando , 1 = esta esperando

    // Politica politica;
    // PN pn;
    int end;
    char *transitions;

    const struct monitor_metodos * metodos;

};

void new_monitor(monitor_o * p_monitor);
