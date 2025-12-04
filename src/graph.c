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

void addEdge(Graph *graph, unsigned char src, unsigned char dest, int weight)
{ 
    if(!graph)
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
    if(y >= graph->n || x >= graph->n || y < 0 || x < 0)
    {
        printf("Error: edge out of bounds\n");
        return;
    }
    if(src != dest)
        graph->cost[y][x] = weight;
}

void printGraph(Graph *graph, print_mode mode)
{
    if(mode == MODE_1)
    {
        for(int y = 0; y < graph->n; y++)
        {
            for(int x = 0; x < graph->n; x++)
                printf("%c %c -> %d\t", y + 'A', x + 'A', graph->cost[y][x]);
            printf("\n");
        }
    }
    else if(mode == MODE_2)
    {
        printf("\t");
        for(int y = 0; y < graph->n; y++)
            printf("%c\t", y + 'A');

        printf("\n\n");
        for(int y = 0; y < graph->n; y++)
        {
            printf("%c\t", y + 'A');
            for(int x = 0; x < graph->n; x++)
                printf("%d\t", graph->cost[y][x]);
            printf("\n\n");
        }
    }
}
void freeGraph(Graph *graph)
{
    if(!graph)
        return;
    int n = graph->n;
    for(int i = 0; i < n; i++)
        free(graph->cost[i]);
    free(graph->cost);
    graph->cost = NULL;
    graph->n = 0;
    free(graph);
    graph = NULL;
}

void freeMatGraph(Graph *graph)
{
    if(!graph)
        return;
    int n = graph->n;
    for(int i = 0; i < n; i++)
        free(graph->cost[i]);
    free(graph->cost);
}
