#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dummy3.h"


//la creacion de los hijos
void creacion_hijos(char N[], char M[],int numero[]){
    int id;
    for(int i = atoi(N); i>0 ;i--){
        id = fork();
        if(id == 0){
            //cierre y copia para los execlp
            dup2(numero[0],0);
            close(numero[0]);

            execlp("./replicante","replicante",M,(char *)0 );
            printf("peto\n");
        }
    }
}
//Indica si el string que le preoporcionamos es un numero entero mas grande o igual que 0
_Bool my_atoi(char a[],int pos){
    int lenght;
    _Bool yes;
    int i;
    i = 0;
    yes = 1;
    lenght = strlen (a);
    for (i=0;yes && i<lenght; i++){
        if (!(isdigit(a[i]))){
            yes = 0;
        }
    }
    return yes;
}

int main(int argc,char *argv[]){
    int i;
    _Bool truth;
    int exitcode, altx;
    int canal,id;
    int numero[2];
    if(argc > 2){
        truth = my_atoi(argv[1],1);
        if(truth && atoi(argv[1]) != 0 ) {
            truth = my_atoi(argv[2],2);
            if(truth && atoi(argv[2]) == 0 ){
                truth = 0;
            }
        }else {
            truth = 0;
        }
        if(!truth){
            printf("Uno o ambos elementos indicados no son numeros enteros\n");
            exit (-1);
        }else{
            pipe(numero);
            canal = open("dummy.dat", O_RDONLY);
            dummy_checkfile(canal);
            id=fork();
            if(!id){
                //cierre y copia para el capitol
                //
                close(numero[0]);
                dup2(numero[1],1);
                close(numero[1]);
                dup2(canal,0);
                close(canal);
                execlp("./capitol","capitol",(char *)0 );
            }
            close(numero[1]);
            creacion_hijos(argv[1], argv[2], numero);
            close(numero[0]);
            i = 0;
            altx = 0;
            while(wait(&exitcode)>0){
                exitcode = (int8_t) WEXITSTATUS(exitcode);
                altx += exitcode;
                if(exitcode == -1) i++;
            }
            if(i > 0){
                printf("%d de los hijos han fallado\n", i);
                exit(-1);
            }
            if(!dummy_testing(altx))exit(0);
            else {
                printf("Algun proceso ha terminado incorrectamente \n");
                exit(-1);
            }
        }
    }else {
        printf("No se han indicado suficientes parametros para ejecutarse, introduzca 2 elementos.\n");
        printf("__________________________________________________________________________________\n");
        printf("La llamada deberia ser por ej'./TT elemento1 elemento2'\n");
        exit (-1);
    }
}