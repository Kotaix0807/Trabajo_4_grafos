#include "tools.h"
#include "ppv.h"
#include <stdio.h>
int main(void){
    int inst = 1, CTY = 0;
    char *args[3] = {0};

    while(inst)
    {
        printf(">ppv ");
        int n = escanf(args, 3, 128);

        if(!strcmp(args[0], "start")){
            ppvStart(&CTY);
            printf("\n");
        }
        else if(!strcmp(args[0], "read")){
            ppvRead(args[1]);
            printf("\n");
        }
        else if(!strcmp(args[0], "exit")){
            ppvExit();
            printf("\n");
            inst = 0;
        }
        else if(args[0] != NULL)
            printf("Comando '%s' no reconocido\n\n", args[0]);
        freeArgs(args, n);
    }
    return 0;
}