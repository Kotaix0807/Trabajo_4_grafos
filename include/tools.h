#include <stdbool.h>

#define ARR_SIZE(a) sizeof(a)/sizeof(a[0])

typedef struct instr{
    char **arg;
    int MAX_ARGS;
    int MAX_CHARS;
}in_str;
/**
 * @brief Inicializa estructura argumentos
 * 
 * @param args Cantidad de argumentos que se desean recibir
 * @param chars Cantidad de caracteres por argumento
 * @return in_str 
 */
in_str initArg(int args, int chars);
/**
 * @brief Esperar input del usuario
 * 
 * @param cur
 */
void escanf(in_str *cur);
/**
 * @brief Liberar memoria de estructura in_str
 * 
 * @param cur 
 */
void freeArgs(in_str *cur);
/**
 * @brief Destruir varible in_str
 * 
 * @param cur
 */
void destroyArgs(in_str *cur);
/**
 * @brief Busqueda binaria booleana
 * 
 * @param arr arreglo
 * @param low bottom
 * @param high tope
 * @param x valor a encontrar
 * @return true si pertenece al arreglo
 * @return false si no pertenece al arreglo
 */
bool binarySearch_bool(int arr[], int low, int high, int x);
/**
 * @brief Verifica si es letra. Si es minuscula, la convierte en mayuscula.
 * 
 * @param c caracter (se modifica en sitio si era minuscula)
 * @return true si era letra A–Z/a–z (quedará en mayuscula)
 * @return false si no era letra
 */
bool verifyCase(unsigned char *c);