#include "graph.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

Graph *initGraph(int n)
{
    Graph *main = NULL;
    if(n <= 0)
    {
        printf("Error: invalid nodes amount for Graph\n");
        return main;
    }
    main = malloc(sizeof(Graph));
    if(!main)
    {
        printf("Error: could not allocate Graph\n");
        return NULL;
    }
    main->n = n;
    main->cost = calloc(n, sizeof(Mat *));
    if(!main->cost)
    {
        printf("Error: could not allocate Graph rows\n");
        free(main);
        return NULL;
    }
    for(int i = 0; i < n; i++)
    {
        main->cost[i] = calloc(n, sizeof(Mat));
        for(int j = 0; j < n; j++)
            main->cost[i][j] = 0;
    }
    return main;
}

void addEdge(Graph *main, unsigned char src, unsigned char dest, int weight)
{ 
    if(!main)
    {
        printf("Error: graph not initialized\n");
        return;
    }
    if(!verifyCase(&src) || !verifyCase(&dest))
    {
        printf("Error: cannot add edge because of invalid character\n");
        return;
    }
    int y = src - 'A';
    int x = dest - 'A';
    if(y >= main->n || x >= main->n || y < 0 || x < 0)
    {
        printf("Error: edge out of bounds\n");
        return;
    }
    if(src != dest)
        main->cost[y][x] = weight;
}

void printGraph(Graph *main, print_mode mode)
{
    if(mode == MODE_1)
    {
        for(int y = 0; y < main->n; y++)
        {
            for(int x = 0; x < main->n; x++)
                printf("%c %c -> %d\t", y + 'A', x + 'A', main->cost[y][x]);
            printf("\n");
        }
    }
    else if(mode == MODE_2)
    {
        printf("\t");
        for(int y = 0; y < main->n; y++)
            printf("%c\t", y + 'A');

        printf("\n\n");
        for(int y = 0; y < main->n; y++)
        {
            printf("%c\t", y + 'A');
            for(int x = 0; x < main->n; x++)
            {
                printf("%d\t", main->cost[y][x]);
            }
            printf("\n\n");
        }

    }
}

void freeGraph(Graph *main)
{
    int n = main->n;
    if(!main)
        return;
    for(int i = 0; i < n; i++)
        free(main->cost[i]);
    free(main->cost);
    main->cost = NULL;
    main->n = 0;
    free(main);
    main = NULL;
}
