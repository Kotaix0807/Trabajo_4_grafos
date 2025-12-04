#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tools.h"

in_str initArg(int args, int chars)
{
    in_str cur;
    cur.MAX_ARGS = args;
    cur.MAX_CHARS = chars;
    cur.arg = calloc(args, sizeof(char *));
    if(!cur.arg)
    {
        perror("calloc error");
        memset(&cur, 0, sizeof(in_str));
        return cur;
    }
    return cur;
}
void escanf(in_str *cur)
{
    if(cur->MAX_ARGS <= 0 || cur->MAX_CHARS <= 0){
        printf("Error: invalid argument or char amount\n");
        return;
    }
    if(!cur->arg){
        printf("Error: arguments buffer not initialized\n");
        return;
    }
    char buffer[cur->MAX_CHARS];
    int count = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL){ // Se obtiene el string de todo lo ingresado por teclado (Se obtiene stdin y se copia al buffer)
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n'){ //Agrega caracter nulo si detecta '\n'
        buffer[len - 1] = '\0';
    }

    char *token = strtok(buffer, " "); // Regla: Separa los strings con ' '
    while (token != NULL && count < cur->MAX_ARGS){
        size_t token_len = strlen(token);

        cur->arg[count] = (char *)malloc(token_len + 1); //Asigna memoria
        if (cur->arg[count] == NULL){
            perror("Error allocating memory");
            break;
        }

        strcpy(cur->arg[count], token); //Una vez alocada la memoria -> Copiar
        count++;

        token = strtok(NULL, " "); //Vacia string guardado en "token"
    }
}
void freeArgs(in_str *cur)
{
    if(!cur || !cur->arg || cur->MAX_ARGS <= 0){
        return;
    }
    for(int i = 0; i < cur->MAX_ARGS; i++){
        free(cur->arg[i]);
        cur->arg[i] = NULL;
    }
}
void destroyArgs(in_str *cur)
{
    if(!cur){
        return;
    }
    freeArgs(cur);
    free(cur->arg);
    cur->arg = NULL;
    cur->MAX_ARGS = 0;
    cur->MAX_CHARS = 0;
}

bool binarySearch_bool(int arr[], int low, int high, int x)
{
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return true;

        if (arr[mid] > x)
            return binarySearch_bool(arr, low, mid - 1, x);

        return binarySearch_bool(arr, mid + 1, high, x);
    }
    return false;
}
bool verifyCase(unsigned char *c)
{
    const int alphabet_size = 26;
    int upper[alphabet_size];
    int lower[alphabet_size];
    for(int i = 0; i < alphabet_size; i++)
    {
        upper[i] = (int)('A' + i);
        lower[i] = (int)('a' + i);
    }
    bool isUpper = binarySearch_bool(upper, 0, alphabet_size - 1, (int)*c);
    bool isLower = binarySearch_bool(lower, 0, alphabet_size - 1, (int)*c);
    #ifdef DEBUG
        printf("Debugging: %c", c);
        printf("Bool_upper: %d\nBool_lower: %d\n", isUpper, isLower);
    #endif
    if(!isUpper && isLower)
        *c -= 32;
    if(!isUpper && !isLower)
        return false;
    return true;
}
