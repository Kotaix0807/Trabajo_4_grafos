#include "tools.h"
#include "ppv.h"

int main(void){
    int inst = 1, CTY = 0;
    in_str menu = initArg(2, 64);

    while(inst)
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
            inst = 0;
        }
        else if(menu.arg[0] != NULL)
            printf("Comando '%s' no reconocido\n\n", menu.arg[0]);
        freeArgs(&menu);
    }
    return 0;
}