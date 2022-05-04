typedef struct politica politica_o;


struct politica_metodos{

    void (*printNumero) (politica_o *);
    int  (*signalPolitic) (politica_o *, int *boolQuesWait);
};

struct politica{
   

    // rdp_o *rdp;
    int numero; //Para probar
    int *listBuff;
    int *addBuffer;
    int *markVector;
    int buffer1, buffer2;
    

    const struct politica_metodos * metodos;
};

//Funciones

void new_politica(politica_o * p_politica);
