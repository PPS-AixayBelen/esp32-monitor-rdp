typedef struct cpuProcess cpuProcess_o;


struct cpuProcess_metodos{

    void (*printNumero) (cpuProcess_o *);
    void  (*run) (cpuProcess_o *);
};

struct cpuProcess{
   
    int numero; //Para probar    
    //monitor_o monitor;
    int *processList; //puntero a lista de transiciones
    const struct cpuProcess_metodos * metodos;
};

//Funciones

void new_cpuProcess(cpuProcess_o * p_cpuProcess, int *processList);
