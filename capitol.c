#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



int main(int argc,char *argv[]){
    char c;
    while(read(0,&c,1)){
        write(1,&c,1);
    }
    exit(0);
}