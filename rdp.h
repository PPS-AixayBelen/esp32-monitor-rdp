typedef struct rdp rdp_o;


struct rdp_metodos{

    void (*printNumero) (rdp_o *);
    int  (*isPos) (rdp_o *,int index);
    void (*updateTimeStamps) (rdp_o *, int * oldSens);
    int * (* getMarkVector)(rdp_o *);
    int * (*getUseBuffer)(rdp_o *);
    int * (*getIsBuffer)(rdp_o *);
    int * (*getCountBuffer)(rdp_o *);
    int * (*getSensitized)(rdp_o *);
    int   (*ifEnd)(rdp_o *);
};

struct rdp{
   
    int numero; //Para probar

    //Cualquier tamaño, despues hay que cambiarlo
    int M[2];
    int B[2];
    int I[2][2];
    int Ipos[2][2];
    int Ineg[2][2];
    int H[2][2];
    int E[2];

    int sensitivedTime[2]; //Cambiar, es de tipo LocalTime. No se como manejar fechas aca
    int minTimeArrival;
    int minTimeSrv1;
    int minTimesSrv2;

    int useBuffers[4];
    int isBuffer[2];
    int isGenTransition[1];
    int isAddBuffer[2];

    int estados;
    int transiciones;
    int dataNumber;
    int packetCounter; //Es boolean

    const struct rdp_metodos * metodos;
};

//Funciones

void new_rdp(rdp_o * p_rdp);
