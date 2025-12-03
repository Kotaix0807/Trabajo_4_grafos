#include "tools.h"
#include "ppv.h"

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
                ppvStart(menu.arg[1], &main);
            }
            else if(!strcmp(menu.arg[0], "read")){
                ppvRead(menu.arg[1]);
            }
            else if(!strcmp(menu.arg[0], "exit")){
                ppvExit();
                freeArgs(&menu);
                printf("\n");
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
    int main(void)
    {
        Graph *main = initGraph(3);
        addEdge(main, 'c', 'A', 13);
        printGraph(main, MODE_2);
        freeGraph(main);
        return 0;
    }
    

#endif
