#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppv.h"
/*TODO: Verificar que no se repitan los caracteres en el archivo (Gestion de errores)*/
void ppvStart(int *CTY){
    FILE *CTY_txt = fopen("CTY.txt", "rb");
    if(!CTY_txt){
        printf("Error: file 'CTY.txt' not found\n");
        return;
    }
    
    if(fseek(CTY_txt, 0, SEEK_END) != 0){
        printf("Error: unable to read 'CTY.txt' size\n");
        fclose(CTY_txt);
        return;
    }
    
    long file_size = ftell(CTY_txt);
    if(file_size < 0){
        printf("Error: unable to determine 'CTY.txt' size\n");
        fclose(CTY_txt);
        return;
    }
    
    rewind(CTY_txt);
    size_t large = (size_t)file_size;
    char *seq = (char *)malloc(large + 1);
    if(!seq){
        printf("Error: malloc failed\n");
        fclose(CTY_txt);
        return;
    }
    
    size_t read_bytes = fread(seq, 1, large, CTY_txt);
    seq[read_bytes] = '\0';
    fclose(CTY_txt);
    
    if(read_bytes == 0){
        printf("Error: 'CTY.txt' is empty\n\n");
        return;
    }
    
    printf("Cities: [%s]\n", seq); //<---------- HALF-END
    *CTY = (int)(strlen(seq) / sizeof(char));
    printf("Large: %d\n", *CTY);
    free(seq);
}

void ppvRead(const char *path){
    if (!path){
        printf("Error: No se especifico ruta o archivo\n");
        return;
    }
    FILE *route = fopen(path, "r");
    if(!route){
        printf("Error: La ruta o archivo '%s' no se encuentra o no existe\n", path);
        return;
    }
}

void ppvGraph(){

    
}

void ppvExit(){


}