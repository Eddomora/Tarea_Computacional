#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VERT 50
#define MAX_ARISTAS 100
#define TAM_ARISTA 2

struct grafo
{
    char vertices[MAX_VERT];
    char aristas[MAX_ARISTAS][TAM_ARISTA];
};

typedef struct grafo grafo_g;

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

    // Formato para separar las palabras del comando a ingresar

    char comando_entrada[256];
    fgets(comando_entrada, 256, stdin);
    comando_entrada[strcspn(comando_entrada, "\n")] = 0;

    char *args[256];
    char *token = strtok(comando_entrada, " ");
    int i = 0;

    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
        if (i >= 256)
            break;
    }

    printf("vertice %c, y arista (%c,%c)", arbol.vertices[0], arbol.aristas[2][0], arbol.aristas[2][1]);

    return 0;
}
