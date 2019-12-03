#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dummy3.h"

int main(int argc,char *argv[]){
    int M,max_size,tiempo;
    M = atoi(argv[1]);
    char buffer[M];
    max_size = 3000;
    if(M > 0 && M <= max_size){
        dummy_init(buffer, M);
        while((tiempo = read(0,&buffer, M))>0){
            dummy_calc(buffer, tiempo);
            usleep(4000);
        }
        dummy_end();
    } else exit(-1);
}





