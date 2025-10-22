#include "utilidades.h"
#include "caminos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct grafo grafo_g;

int main(int argc, char const *argv[])
{
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
            printf("Error, comando mal escrito\n");
            continue;
            ;
        }

        int G[MAX][MAX];
        memset(G, 0, sizeof(int) * MAX * MAX);
        if (strcasecmp(palabras[3], "planar") == 0 && verificar(*palabras[1], planar) && verificar(*palabras[2], planar))
        {
            printf("- Grafo sin orientacion\n");
            creacion_grafico(G, planar);
            dijkstra(G, strlen(planar.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 1\n");
            orientacion1(G, planar);
            dijkstra(G, strlen(planar.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 2\n");
            orientacion2(G, planar);
            dijkstra(G, strlen(planar.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 3\n");
            orientacion3(G, planar);
            dijkstra(G, strlen(planar.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 4\n");
            orientacion4(G, planar);
            dijkstra(G, strlen(planar.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
        }
        else if (strcasecmp(palabras[3], "arbol") == 0 && verificar(*palabras[1], arbol) && verificar(*palabras[2], arbol))
        {
            printf("- Grafo sin orientacion\n");
            creacion_grafico(G, arbol);
            dijkstra(G, strlen(arbol.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 1\n");
            orientacion1(G, arbol);
            dijkstra(G, strlen(arbol.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 2\n");
            orientacion2(G, arbol);
            dijkstra(G, strlen(arbol.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 3\n");
            orientacion3(G, arbol);
            dijkstra(G, strlen(arbol.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 4\n");
            orientacion4(G, arbol);
            dijkstra(G, strlen(arbol.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
        }
        else if (strcasecmp(palabras[3], "euleriano") == 0 && verificar(*palabras[1], euleriano) && verificar(*palabras[2], euleriano))
        {
            printf("- Grafo sin orientacion\n");
            creacion_grafico(G, euleriano);
            dijkstra(G, strlen(euleriano.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 1\n");
            orientacion1(G, euleriano);
            dijkstra(G, strlen(euleriano.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 2\n");
            orientacion2(G, euleriano);
            dijkstra(G, strlen(euleriano.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 3\n");
            orientacion3(G, euleriano);
            dijkstra(G, strlen(euleriano.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
            memset(G, 0, sizeof(int) * MAX * MAX);

            printf("- Grafo con la orientacion 4\n");
            orientacion4(G, euleriano);
            dijkstra(G, strlen(euleriano.vertices), char_a_index(*palabras[1]), char_a_index(*palabras[2]));
        }
        else
        {
            printf("\nGrafo no encontrado intente nuevamente\n");
            continue;
        }
    }

    return 0;
}
