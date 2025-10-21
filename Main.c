#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VERT 50
#define MAX_ARISTAS 100
#define TAM_ARISTA 2
#define MAX 12
#define INFINITO 9999999

struct grafo
{
    char vertices[MAX_VERT];
    char aristas[MAX_ARISTAS][TAM_ARISTA];
};

typedef struct grafo grafo_g;

int char_to_index(char c)
{
    return tolower((unsigned char)c) - 'a';
}
char index_to_char(int i)
{
    return (char)('a' + i);
}

void dijkstra(int n, int nodo_inicio, int nodo_final)
{
    int G[MAX][MAX], dist[MAX], pred[MAX], visitado[MAX];

    // 1. Inicialización
    for (int i = 0; i < n; ++i)
    {
        dist[i] = INFINITO;
        pred[i] = -1;
        visitado[i] = 0;
    }
    dist[nodo_inicio] = 0;

    // 2. Bucle principal de Dijkstra
    for (int step = 0; step < n; ++step)
    {
        int u = -1;
        int best = INFINITO;
        for (int i = 0; i < n; ++i)
        {
            if (!visitado[i] && dist[i] < best)
            {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break; // No quedan nodos alcanzables

        visitado[u] = 1;
        if (u == nodo_final)
            break; // Corte temprano: alcanzamos el destino

        for (int v = 0; v < n; ++v)
        {
            // Verificamos si hay una arista (peso > 0) y si el destino no ha sido visitado
            if (!visitado[v] && G[u][v] != 0)
            {
                int w = G[u][v];
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
            }
        }
    }

    // 3. Resultado y reconstrucción del camino
    if (dist[nodo_final] >= INFINITO / 2) // Usar INFINITO/2 para evitar desbordamiento
    {
        printf("\nNo existe un camino entre '%c' y '%c'.\n", index_to_char(nodo_inicio), index_to_char(nodo_final));
        return;
    }

    // reconstruir camino
    int path[MAX], len = 0;
    for (int cur = nodo_final; cur != -1; cur = pred[cur])
    {
        path[len] = cur;
        len++;
        if (cur == nodo_inicio)
            break;
    }

    printf("\nLa distancia mas corta de '%c' a '%c' es: %d\n", index_to_char(nodo_inicio), index_to_char(nodo_final), dist[nodo_final]);

    printf("El camino es: ");

    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c", path[i]);
        if (i)
            printf(" -> ");
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // esta parte puede que sea mejor agregarla con un .h
    grafo_g arbol = {
        .vertices = "abcdefghijkl",
        .aristas = {{'a', 'b'}, {'a', 'c'}, {'b', 'd'}, {'d', 'h'}, {'d', 'i'}, {'c', 'e'}, {'c', 'f'}, {'c', 'g'}, {'g', 'l'}, {'f', 'j'}, {'f', 'k'}}};

    grafo_g planar = {
        .vertices = "abcdefghi",
        .aristas = {{'a', 'b'}, {'a', 'h'}, {'b', 'h'}, {'b', 'd'}, {'b', 'c'}, {'c', 'd'}, {'d', 'i'}, {'d', 'f'}, {'d', 'e'}, {'e', 'f'}, {'f', 'i'}, {'f', 'h'}, {'f', 'g'}, {'g', 'h'}}};

    grafo_g euleriano = {
        .vertices = "abcdefghij",
        .aristas = {{'a', 'b'}, {'a', 'h'}, {'b', 'c'}, {'b', 'j'}, {'b', 'h'}, {'c', 'j'}, {'c', 'd'}, {'c', 'e'}, {'d', 'j'}, {'d', 'i'}, {'d', 'e'}, {'e', 'j'}, {'e', 'i'}, {'e', 'f'}, {'e', 'g'}, {'f', 'i'}, {'f', 'h'}, {'f', 'g'}, {'g', 'i'}, {'g', 'h'}, {'h', 'i'}, {'h', 'j'}, {'i', 'j'}}};

    char comando_entrada[256];
    while (1)
    {
        printf("Ingrese el camino que desea probar (Ej: path a b Euleriano): ");
        fgets(comando_entrada, 256, stdin);
        comando_entrada[strcspn(comando_entrada, "\n")] = 0;

        char *palabras[256];
        char *token = strtok(comando_entrada, " ");
        int i = 0;

        while (token != NULL)
        {
            palabras[i] = token;
            token = strtok(NULL, " ");
            i++;
            if (i >= 256)
                break;
        }

        if (strcasecmp(palabras[0], "exit") == 0)
        {
            break;
        }

        if (strlen(*palabras) != 4)
        {
            printf("Error, comando mal escrito");
            continue;
            ;
        }

        if (strcasecmp(palabras[3], "planar") == 0)
        {
            dijkstra(strlen(planar.vertices), char_to_index(*palabras[1]), char_to_index(*palabras[2]));
        }
        else if (strcasecmp(palabras[3], "arbol") == 0)
        {
            dijkstra(strlen(arbol.vertices), char_to_index(*palabras[1]), char_to_index(*palabras[2]));
        }
        else if (strcasecmp(palabras[3], "euleriano") == 0)
        {
            dijkstra(strlen(euleriano.vertices), char_to_index(*palabras[1]), char_to_index(*palabras[2]));
        }
        else
        {
            printf("Grafo no encontrado intente nuevamente");
            continue;
        }

        printf("vertice %c, y arista (%c,%c)", arbol.vertices[0], arbol.aristas[2][0], arbol.aristas[2][1]);
    }

    return 0;
}
