#include "tools.h"
#include "pvv.h"

//#define DEBUG

#ifndef DEBUG
#include <stdio.h>
#include <string.h>
    int main(void)
    {
        in_str menu = initArg(2, 64);
        Graph *main = NULL;

        while(1)
        {
            printf(">ppv ");
            escanf(&menu);
            if(!strcmp(menu.arg[0], "start")){
                pvvStart(menu.arg[1], &main);
            }
            else if(!strcmp(menu.arg[0], "read")){
                pvvRead(menu.arg[1], &main);
            }
            else if(!strcmp(menu.arg[0], "print")){
                pvvGraph(main, menu.arg[1]);
            }
            else if(!strcmp(menu.arg[0], "exit")){
                pvvExit();
                freeArgs(&menu);
                break;
            }
            else if(menu.arg[0] != NULL)
                printf("Comando '%s' no reconocido\n\n", menu.arg[0]);
            freeArgs(&menu);
            printf("\n");
        }
        destroyArgs(&menu);
        freeGraph(main);
        return 0;
    }

#else
#include <stdio.h>
#include <string.h>
    int main(void)
    {
        char linea[] = "hola como estas amigo";
        
        char *token = strtok(linea, " ");

        while (token != NULL)
        {
            printf("Token: '%s'\n", token);
            token = strtok(NULL, " "); //Cuando es NULL, se avanza con el string anterior, NO SE LIMPIA
        }

        return 0;
    }
    

#endif
