 #include <stdbool.h>
typedef int Mat;

typedef struct 
{
    int n; //Numero de ciudades
    int **cost;//Matriz de adyacencia
} Graph;

typedef enum{
    MODE_1 = 0,
    MODE_2
}print_mode;

Graph *initGraph(int n);
void addEdge(Graph *main, unsigned char src, unsigned char dest, int weight);
void printGraph(Graph *main, print_mode mode);
void freeGraph(Graph *main);
void freeMatGraph(Graph *graph);
void DFS(Graph* graph, int j, int count, int cost, int* min_cost, bool* visited, int* path, int* best_path);
void hamilton(Graph *graph);

