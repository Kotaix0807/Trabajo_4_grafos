#include <stdio.h>
#include <stdlib.h>
#include "ppv.h"
/*TODO: Verificar que no se repitan los caracteres en el archivo (Gestion de errores)*/
void ppvStart(char *arg, Graph **graph)
{
    int n_cities;
    if(!arg)
    {
        printf("Error: no input\n");
        printf("Use: 'start <n_cities>'\n");
        printf("Type 'help' 'h' '-h' for more help\n");
        return;
    }
    if((n_cities = atoi(arg)) <= 0)
    {
        printf("Error: invalid number assign\n");
        return;
    }
    Graph *tmp = initGraph(n_cities);
    if(!tmp)
    {
        printf("Error: graph allocation failed\n");
        return;
    }
    if(graph && *graph)
        freeGraph(*graph);
    if(graph)
        *graph = tmp;
    printf("Graph initialized with '%d' cities\n", n_cities);
}

void ppvRead(const char *path, Graph **graph)
{
    if (!path)
    {
        printf("Error: No se especifico ruta o archivo\n");
        return;
    }
    FILE *route = fopen(path, "r");
    if(!route)
    {
        printf("Error: La ruta o archivo '%s' no se encuentra o no existe\n", path);
        fclose(route);
        return;
    }
    unsigned char a, b;
    int weight;
    int secure_fscanf;
    while((secure_fscanf = fscanf(route, "%c %c %d\n", &a, &b, &weight)) != EOF)
    {
        if(secure_fscanf != 3)
        {
            printf("Error: Poorly written txt route\n");
            printf("Hint: Make sure your file is correct\n");
            fclose(route);
            freeMatGraph(*graph);
            return;
        }
        addEdge(*graph, a, b, weight);
    }
}

void ppvGraph(Graph *graph, char *mode)
{
    print_mode current = 0;
    int result;
    if(!mode)
    {
        printf("Error: no mode especified\n");
        return;
    }
    if((result = (atoi(mode) - 1)) <= -1)
    {
        printf("Error: mode '%d' does not exists\n", result);
        return;
    }
    current = result;
    printGraph(graph, current);
    return;
}

void ppvExit()
{
    return;

}

/* Read file


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
*/
