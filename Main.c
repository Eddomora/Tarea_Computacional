#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERT 50
#define MAX_ARISTAS 100
#define TAM_ARISTA 3

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
        .vertices = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', '\0'},
        .aristas = {"ab", "ac", "bd", "dh", "di", "ce", "cf", "cg", "gl", "fj", "fk", '\0'}};

    grafo_g planar = {
        .vertices = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'},
        .aristas = {"ab", "ah", "bh", "bd", "bc", "cd", "di", "df", "de", "ef", "fi", "fh", "fg", "gh", '\0'}};

    grafo_g euleriano = {
        .vertices = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0'},
        .aristas = {"ab", "ah", "bc", "bj", "bh", "cj", "cd", "ce", "dj", "di", "de", "ej", "ei", "ef", "eg", "fi", "fh", "fg", "gi", "gh", "hi", "hj", "ij", '\0'}};

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

    return 0;
}
