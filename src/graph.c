#include "graph.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //para evitar desbordamientos 

Graph *initGraph(int n)
{
    Graph *main = NULL;
    if(n <= 0) { printf("Error: invalid nodes amount\n"); return main; }
    main = malloc(sizeof(Graph));
    if(!main) return NULL;
    main->n = n;
    main->cost = calloc(n, sizeof(Mat *));
    for(int i = 0; i < n; i++) {
        main->cost[i] = calloc(n, sizeof(Mat));
    }
    return main;
}

void addEdge(Graph *graph, unsigned char src, unsigned char dest, int weight)
{ 
    if(!graph) return;
    if(!verifyCase(&src) || !verifyCase(&dest)) return;
    int y = src - 'A';
    int x = dest - 'A';
    if(y >= graph->n || x >= graph->n || y < 0 || x < 0) return;
    if(src != dest) {
        graph->cost[y][x] = weight;
        graph->cost[x][y] = weight;
    }
}

void printGraph(Graph *graph, print_mode mode)
{
    if(!graph) return;
    if(mode == MODE_1) {
        for(int y = 0; y < graph->n; y++) {
            for(int x = 0; x < graph->n; x++)
                printf("%c %c -> %d\t", y + 'A', x + 'A', graph->cost[y][x]);
            printf("\n");
        }
    } else if(mode == MODE_2) {
        printf("\t");
        for(int y = 0; y < graph->n; y++) printf("%c\t", y + 'A');
        printf("\n\n");
        for(int y = 0; y < graph->n; y++) {
            printf("%c\t", y + 'A');
            for(int x = 0; x < graph->n; x++) printf("%d\t", graph->cost[y][x]);
            printf("\n\n");
        }
    }
}

void freeGraph(Graph *graph)
{
    if(!graph) return;
    for(int i = 0; i < graph->n; i++) free(graph->cost[i]);
    free(graph->cost);
    free(graph);
}

void tsp_backtracking(Graph *graph, int currPos, int count, int cost, int *min_cost, bool *visited, int *path, int *best_path)
{
    if (cost >= *min_cost) return; // Poda

    if (count == graph->n) {
        if (graph->cost[currPos][0] > 0) {
            int total_cost = cost + graph->cost[currPos][0];
            if (total_cost < *min_cost) {
                *min_cost = total_cost;
                for (int i = 0; i < graph->n; i++) best_path[i] = path[i];
                best_path[graph->n] = 0; 
            }
        }
        return;
    }

    for (int i = 0; i < graph->n; i++) {
        if (!visited[i] && graph->cost[currPos][i] > 0) {
            visited[i] = true;
            path[count] = i;
            tsp_backtracking(graph, i, count + 1, cost + graph->cost[currPos][i], min_cost, visited, path, best_path);
            visited[i] = false;
        }
    }
}
void DFS(Graph *graph, int j, int count, int cost, int *min_cost, bool *visited, int *path, int *best_path)
{
    // 1. PODA DEL ÁRBOL: Si el camino actual ya es muy caro, cortamos esta rama.
    if (cost >= *min_cost) return; 
    // 2. MARCAR: Estamos en el nodo 'u'
    visited[j] = true;
    path[count - 1] = j;

    // 3. CASO BASE (Hoja del árbol): Hemos visitado todas las ciudades
    if (count == graph->n) {
        // Verificamos si podemos volver al origen (0) para cerrar el ciclo
        if (graph->cost[j][0] > 0) {
            int total_cost = cost + graph->cost[j][0];
            // Si encontramos un mejor precio, guardamos esta ruta
            if (total_cost < *min_cost) {
                *min_cost = total_cost;
                for (int i = 0; i < graph->n; i++) best_path[i] = path[i];
                best_path[graph->n] = 0; // Cerrar el ciclo en A
            }
        }
    } 
    else {
        // 4. RECURSIÓN (Ramas): Explorar vecinos no visitados
        for (int v = 0; v < graph->n; v++) {
            if (!visited[v] && graph->cost[j][v] > 0) 
            {
                // Llamada recursiva: Profundizar en el árbol
                DFS(graph, v, count + 1, cost + graph->cost[j][v], min_cost, visited, path, best_path);
            }
        }
    }

    // 5. BACKTRACKING: Desmarcar al salir para permitir otros caminos en el futuro
    visited[j] = false;
}

void hamilton(Graph *graph)
{
    if(!graph || graph->n < 2) return;
    
    printf("Verificando que existe una ruta.\n");
    int n = graph->n;
    bool *visited = calloc(n, sizeof(bool));
    int *path = calloc(n + 1, sizeof(int));
    int *best_path = calloc(n + 1, sizeof(int));
    int min_cost = INT_MAX;

    visited[0] = true;
    path[0] = 0;

    tsp_backtracking(graph, 0, 1, 0, &min_cost, visited, path, best_path);

    if (min_cost == INT_MAX) {
        printf("No existe un camino que recorra todos las ciudades y regrese a la ciudad de origen.\n");
    } else {
        printf("Existe un camino que recorra todos las ciudades y regresa a la ciudad de origen.\n");
        printf("Ruta a seguir: ");
        for (int i = 0; i < n; i++) printf("%c", best_path[i] + 'A');
        printf("A\n");
        printf("Costo total minimo: %d\n", min_cost);
    }
    free(visited); free(path); free(best_path);
}

