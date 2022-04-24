#include <stdio.h>
#include "rdp.h"


int main(){

rdp_o myrdp;

new_rdp(&myrdp);

myrdp.metodos->printNumero(&myrdp);

}