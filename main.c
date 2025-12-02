#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tools.h"
#include "ppv.h"

int main(void){
    int CTY = 0;
    in_str menu = initArg(2, 64);

    while(1)
    {
        printf(">ppv ");
        escanf(&menu);
        if(!strcmp(menu.arg[0], "start")){
            ppvStart(&CTY);
            printf("\n");
        }
        else if(!strcmp(menu.arg[0], "read")){
            ppvRead(menu.arg[1]);
            printf("\n");
        }
        else if(!strcmp(menu.arg[0], "exit")){
            ppvExit();
            printf("\n");
            freeArgs(&menu);
            break;
        }
        else if(menu.arg[0] != NULL)
            printf("Comando '%s' no reconocido\n\n", menu.arg[0]);
        freeArgs(&menu);
    }
    destroyArgs(&menu);
    return 0;
}
