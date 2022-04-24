typedef struct rdp rdp_o;


struct rdp_metodos{
    void (*printNumero) (rdp_o *);
};

struct rdp{

    int numero;
    const struct rdp_metodos * metodos;
};

//Funciones
void new_rdp(rdp_o * p_rdp);